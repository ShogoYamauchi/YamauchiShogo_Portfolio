//--------------------------------------------------------------------
// �t�@�C�����FPoliceAttackComponent.cpp
// �T�v�@�@�@�F�x�@�i�G�j�̍U������R���|�[�l���g
// �쐬�ҁ@�@�F�R���@����
// �X�V���e�@�F2024/12/03	�N���X�̍쐬
//--------------------------------------------------------------------

#include "PoliceAttackComponent.h"
#include "EnemyBullet.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "LineControllerComponent.h"
#include "Components/SplineComponent.h"

// �R���X�g���N�^
UPoliceAttackComponent::UPoliceAttackComponent()
	: _owner(UEnemyAttackComponent::GetOwner())
	, _canAttackTimer(0.0f)
	, _bulletTimer(0.0f)
	, _hasFired(false)
{
	// ���t���[���A���̃N���X��Tick()���ĂԂ��ǂ��������߂�t���O
	// �K�v�ɉ����āA�p�t�H�[�}���X����̂��߂ɐ؂邱�Ƃ��ł���B
	PrimaryComponentTick.bCanEverTick = true;
}

// �Q�[���X�^�[�g���A�܂��͐������ɌĂ΂�鏈��
void UPoliceAttackComponent::BeginPlay()
{
	Super::BeginPlay();

	// �R���|�[�l���g�̎擾
	_pLineControllerComponent = GetOwner()->FindComponentByClass<ULineControllerComponent>();		// �\�������o�����߂̃R���|�[�l���g
	if (!_pLineControllerComponent)
	{
		// �f�o�b�O�p
		//UE_LOG(LogTemp, Warning, TEXT("LineControllerComponent not found on Owner"));
	}

	// �Ë����� 
	// �w�肵���p�x�ɉ�]
	FRotator NewRotation(0.0f, 180.0f, 0.0f);
	_owner->SetActorRotation(NewRotation);  // Actor���w�肵����]�ɐݒ�

	// �Ë�����
	FName ItemTag = "Item";
	FName SmogTag = "Smog";
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), ItemTag, _pItems);
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), SmogTag, _pSmogs);

	// �g���[�X�p�̃N�G���p�����[�^��ݒ�
	_queryParamsToTrace.AddIgnoredActor(_owner);	// �����̃L�����N�^�[�𖳎�
	_queryParamsToTrace.AddIgnoredActors(_pSmogs);	// ���S�Ă��𖳎�
	_queryParamsToTrace.AddIgnoredActors(_pItems);	// �A�C�e���S�Ă𖳎�
}

// ���t���[������
void UPoliceAttackComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	// �o�ߎ��Ԃ̌v��
	_canAttackTimer += DeltaTime;
	
	// �w�肵�����Ԍo�߂�����\�������o���đł\��������
	if (_timeToAttack <= _canAttackTimer)
	{
		EnemyState = EnemyStatus::Style;
		_isAttackAble = true;
	}
}

// �֐����FEnemyAttack 
// �����F�P�t���[���ɂ����鎞��
// �߂�l�F�Ȃ�
// ���e�F�x�@�̍U�����s���I�[�o�[���b�v�֐��@
void UPoliceAttackComponent::EnemyAttack(float deltaTime)
{
	// �y�f�o�b�O�p�z
	//UE_LOG(LogTemp, Log, TEXT("Invoke PoliceAttack()"));

	// NULL�`�F�b�N	
	if (!EnemyBulletClass) {/* UE_LOG(LogTemp, Warning, TEXT("Nothing EnemyBullet"));*/ return; }	// ��������e�����邩�ǂ����`�F�b�N
	if (!_owner) { /*UE_LOG(LogTemp, Warning, TEXT("Failed To Acquire Owner"));*/  return; }		// �R���|�[�l���g�̃I�[�i�[�ł��� Actor �����邩�`�F�b�N

	// �o�ߎ��Ԃ̌v��
	_bulletTimer += deltaTime;

	// �\�������o��
	DrawPredictionSplineWithCollision(deltaTime);

	// �N�[���^�C������
	if (!_hasFired) // �܂��e�𔭎˂��Ă��Ȃ��ꍇ
	{
		// �\���Ă����ԁi�\�������o���j
		if (_bulletTimer <= _timeToFire - _predictionStopToFireInterval)
		{
			// �\������\���ɂ���
			if (!_pLineControllerComponent) { /*UE_LOG(LogTemp, Warning, TEXT("Not _pLineControllerComponent"));*/ return; }
			_pLineControllerComponent->DisplayPredictionLineActor();
		}
		// �ł��������܂��Ă��ė\�����������鎞��
		else if (_timeToFire - _predictionStopToFireInterval <= _bulletTimer)
		{
			// �\�������\���ɂ���
			if (!_pLineControllerComponent) { /*UE_LOG(LogTemp, Warning, TEXT("Not _pLineControllerComponent"));*/ return; }
			_pLineControllerComponent->HidePredictionLineActor();
		}
		// �e��ł�
		if (_timeToFire <= _bulletTimer)
		{
			EnemyState = EnemyStatus::Fire;
			SpawnBullet();         // �e�𔭎�
			_hasFired = true;      // ���˃t���O�𗧂Ă�
			_bulletTimer = 0.0f;   // �^�C�}�[�����Z�b�g
		}
	}
	else // ���ˌ�̃N�[���^�C�����v��
	{
		if (_enemyAttackCooldown <= _bulletTimer)
		{
			EnemyState = EnemyStatus::Style;
			_bulletTimer = 0.0f;   // �N�[���_�E���I���A�^�C�}�[�����Z�b�g
			_hasFired = false;     // �Ăє��ˉ\�ɂ���
		}
	}
}

// �֐����FSpawnBullet
// �����F�Ȃ�
// �߂�l�F�Ȃ�
// ���e�G�e���C���X�^���X������֐�
void UPoliceAttackComponent::SpawnBullet()
{
	// ���ˈʒu������iPolice�̈ʒu + �x�@�������Ă������(�P�ʃx�N�g��) * _enemyBulletOffset�j
	FVector _spawnLocation = _owner->GetActorLocation() + _owner->GetActorForwardVector() * _enemyBulletOffset;
	// Actor�̌����i�O���x�N�g���j
	FRotator _spawnRotation = _owner->GetActorRotation();

	// EnemyBullet �𐶐�
	AEnemyBullet* _pSpawnedEnemyBullet = GetWorld()->SpawnActor<AEnemyBullet>(EnemyBulletClass, _spawnLocation, _spawnRotation);

	if (_pSpawnedEnemyBullet)
	{
		_pSpawnedEnemyBullet->SetDirection(_owner->GetActorForwardVector());
		_pSpawnedEnemyBullet->SetBulletSpeed(_bulletSpeed);
		_pSpawnedEnemyBullet->SetOwner(_owner);
	}
 }

// �֐����FDrawPredictionSplineWithCollision
// �����F�P�t���[���ɂ����鎞��
// �߂�l�F�Ȃ�
// ���e�F�����̈ʒu����O���ɗ\�������o���֐�
void UPoliceAttackComponent::DrawPredictionSplineWithCollision(float deltaTime)
{
	if (!_pLineControllerComponent) { /*UE_LOG(LogTemp, Warning, TEXT("Not _pLineControllerComponent"));*/ return; }

	// �x�@�̈ʒu�ƌ����Ă���������擾
	FVector _start = _owner->GetActorLocation();  // �x�@�̈ʒu
	FRotator _rotation = _owner->GetActorRotation();  // �x�@�̉�]
	FVector _forwardDirection = _rotation.Vector();  // �x�@�̌����Ă�������̃x�N�g��

	// �����΂��������w��
	float _traceDistance = 5000.0f;
	FVector _end = _start + _forwardDirection * _traceDistance;  // �I�_�̈ʒu

	// �Փ˔���
	FHitResult HitResult;

	// Line Trace ���s
	bool bHit = GetWorld()->LineTraceSingleByObjectType(HitResult, _start, _end, FCollisionObjectQueryParams::AllObjects, _queryParamsToTrace);
	if (bHit)
	{
		// �Փ˂����ꍇ�A�q�b�g�����ꏊ�ɑ΂��鏈��
		//UE_LOG(LogTemp, Log, TEXT("Hit: %s"), *HitResult.GetActor()->GetName());	// �Փˑ�����o��
		//UE_LOG(LogTemp, Log, TEXT("Hit at: %s"), *HitResult.ImpactPoint.ToString());  // �Փ˓_�̍��W�����O�ɏo��

		// �q�b�g�����A�N�^�[���擾
		AActor* _pHitActor = HitResult.GetActor();
		if (_pHitActor)
		{
			// �q�b�g�����A�N�^�[�̍��W���擾
			_end = HitResult.Location; // -ForwardDirection * 350.0f;  // ������O�ɒ���
		}
		// �Փ˂���Actor��\��
		//UE_LOG(LogTemp, Log, TEXT("Hit Actor: %s"), *HitActor->GetName());
	}
	//else
	//{
	//  // �f�o�b�O�p
	//	// �Փ˂��Ȃ������ꍇ
	//	//UE_LOG(LogTemp, Log, TEXT("No hit"));
	//}

	// �f�o�b�O���C
	//DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 1.0f, 0, 1.0f);

	// �f�o�b�O�p
	//UE_LOG(LogTemp, Log, TEXT("PoliceAttackComopnent Start: %s, End: %s"), *Start.ToString(), *End.ToString());

	// �\�����̍X�V
	_pLineControllerComponent->UpdateLineActor(_start, _end);
}