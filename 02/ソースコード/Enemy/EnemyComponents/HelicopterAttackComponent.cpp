//--------------------------------------------------------------------
// �t�@�C�����FHelicopterAttackComponent.cpp
// �T�v�@�@�@�F�w���R�v�^�[�i�G�j�̍U������R���|�[�l���g
// �쐬�ҁ@�@�F�R���@����
// �X�V���e�@�F2024/12/31	�N���X�̍쐬
//--------------------------------------------------------------------

#include "HelicopterAttackComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "EnemyBullet.h"
#include "LineControllerComponent.h"
#include "Components/SplineComponent.h"

// �R���X�g���N�^
UHelicopterAttackComponent::UHelicopterAttackComponent()
	: _playerActor(nullptr)
	, _owner(UEnemyAttackComponent::GetOwner())
	, _moveTargetActor(nullptr)
	, _pLineControllerComponent(nullptr)
	, _startPointToDrawPrediction(0.0f, 0.0f, 0.0f)
	, _endPointToDrawPrediction(0.0f, 0.0f, 0.0f)
	, _rotationToFire(0.0f,0.0f,0.0f)
	, _canAttackTimer(0.0f)
	, _bulletTimer(0.0f)
	, _hasFired(false)
{
	// ���t���[���A���̃N���X��Tick()���ĂԂ��ǂ��������߂�t���O
	// �K�v�ɉ����āA�p�t�H�[�}���X����̂��߂ɐ؂邱�Ƃ��ł���B
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// �Q�[���X�^�[�g���A�܂��͐������ɌĂ΂�鏈��
void UHelicopterAttackComponent::BeginPlay()
{
	Super::BeginPlay();

	// �����w�����X�e�[�W�ɑ��݂���ꍇ�͏���
	TArray<AActor*> _searchHelicopters;
	// ���[���h����^�O�Ɉ�v����A�N�^�[���擾
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("Helicopter"), _searchHelicopters);
	// ���������A�N�^�[�ɑ΂��ď������s��
	for (AActor* Actor : _searchHelicopters)
	{
		if (Actor != this->_owner)
		{
			// �f�o�b�O�p
			//UE_LOG(LogTemp, Warning, TEXT("The helicopter is already there."));
			// ����
			this->_owner->Destroy();

			return;
		}
	}


	// �R���|�[�l���g�̎擾
	_pLineControllerComponent = GetOwner()->FindComponentByClass<ULineControllerComponent>();		// �\�������o�����߂̃R���|�[�l���g
	if (!_pLineControllerComponent)
	{
		// �f�o�b�O�p
		//UE_LOG(LogTemp, Warning, TEXT("LineControllerComponent not found on Owner"));
	}

	// �^�O�����A�N�^�[�̔z���錾
	TArray<AActor*> _foundActors;

	// ���[���h����^�O�Ɉ�v����A�N�^�[���擾
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("Player"), _foundActors);

	// ���������A�N�^�[�ɑ΂��ď������s��
	for (AActor* Actor : _foundActors)
	{
		if (Actor)
		{
			// �v���C���[�A�N�^�[��ێ�����
			_playerActor = Actor;
			//UE_LOG(LogTemp, Log, TEXT("Found Actor: %s"), *Actor->GetName());
		}
	}

	// �Ë�����
	TArray<AActor*> _searchMoveTargetActors;
	// ���[���h����^�O�Ɉ�v����A�N�^�[���擾
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), FName("MoveTarget"), _searchMoveTargetActors);
	// ���������A�N�^�[�ɑ΂��ď������s��
	for (AActor* Actor : _searchMoveTargetActors)
	{
		UE_LOG(LogTemp, Log, TEXT("MoveTargetActor is Active"));
		if (Actor->ActorHasTag("Right"))
		{
			// �o�^
			_moveTargetActors[0] = Actor;
		}
		if (Actor->ActorHasTag("Center"))
		{
			// �o�^
			_moveTargetActors[1] = Actor;
		}
		if (Actor->ActorHasTag("Left"))
		{
			// �o�^
			_moveTargetActors[2] = Actor;
		}
	}

	// ���C�L���X�g�Ŗ�������A�N�^�[�������E�ێ�
	FName _itemTag = "Item";
	FName _smogTag = "Smog";
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), _itemTag, _pItems);
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), _smogTag, _pSmogs);

	// �g���[�X�p�̃N�G���p�����[�^��ݒ�
	_queryParamsToTrace.AddIgnoredActor(_owner);	// �����̃L�����N�^�[�𖳎�
	_queryParamsToTrace.AddIgnoredActors(_pSmogs);	// ���S�Ă��𖳎�
	_queryParamsToTrace.AddIgnoredActors(_pItems);	// �A�C�e���S�Ă𖳎�

	// �ړ��ڕW�A�N�^�[��ݒ�
	// �Ë�����
	TSubclassOf<AStageManager> _findClass;
	_findClass = AStageManager::StaticClass();

	AActor* stageManager = UGameplayStatics::GetActorOfClass(GetWorld(), _findClass);
	SetMoveTargetNumber(Cast<AStageManager>(stageManager)->GetHeliStatus());
	_setMoveTargetActor();
}

// ���t���[������
void UHelicopterAttackComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// �ڕW�n�_�܂ňړ�����
	_moveToTargetLocation(DeltaTime);

	// �f�o�b�O�p
	//_isAttackAble = true;	// �U���\�ɂ���
}

// �֐����F_moveToTargetLocation
// �����F_deltaTime�F�P�t���[���ɂ�����b��
// �߂�l�F�Ȃ�
// ���e�F�^�[�Q�b�g�̃|�C���g�܂ňړ�����֐�
void UHelicopterAttackComponent::_moveToTargetLocation(float deltaTime)
{
	if (!_owner) { /*UE_LOG(LogTemp, Warning, TEXT("Helicopter / Failed To Acquire Owner"));*/ return; }		// �R���|�[�l���g�̃I�[�i�[�ł��� Actor �����邩�`�F�b�N
	if (!_moveTargetActor) { /*UE_LOG(LogTemp, Warning, TEXT("Helicopter / Failed To Acquire MoveTargetActor"));*/ return; }		// �ڕW�n�_�� Actor �����邩�`�F�b�N

	FVector StartLocation = _owner->GetActorLocation();   // ���݂̈ʒu��ݒ�
	FVector TargetLocation = _moveTargetActor->GetActorLocation();  // �ڕW�n�_�̎擾

	// �o�ߎ��Ԃ��X�V
	_canAttackTimer += deltaTime;

	// �ړ����̏���
	if (_canAttackTimer < _canAttackTime)
	{
		//UE_LOG(LogTemp, Log, TEXT("Helicopter is Moving"));
		// ���`�i�s�x���v�Z
		// �Ë�����
		float _linearAlpha = FMath::Clamp(_canAttackTimer / _canAttackTime * 0.02f, 0.0f, 1.0f);

		// �C�[�W���O�֐���K�p
		// EaseAlpha��0�`1�͈̔͂Ɏ��߂�
		float _easeAlpha = FMath::Clamp(FMath::InterpEaseOut(0.0f, 1.0f, _linearAlpha, 2.0f), 0.0f, 1.0f);

		// �V�����ʒu���v�Z
		FVector _newLocation = FMath::Lerp(StartLocation, TargetLocation, _easeAlpha);

		// �V�����ʒu�ɃA�N�^�[���ړ�
		_owner->SetActorLocation(_newLocation);
	}
	else
	{
		// �o�ߎ��Ԃ��ړ����ԂɒB������ړ��I��
		// �Ë�����
		//_owner->SetActorLocation(TargetLocation);  // �ŏI�I�Ȉʒu�ɕ␳
		// �Ë�����
		if (_canAttackTime + _timeToAttack < _canAttackTimer)
		{
			_isAttackAble = true;	// �U���\�ɂ���
		}
	}
}

// �֐����FEnemyAttack
// �����F�P�t���[���ɂ����鎞��
// �߂�l�F�Ȃ�
// ���e�F�U�����d�|����֐�(�e�̗\�������o���Ēe�𔭎˂���)
void UHelicopterAttackComponent::EnemyAttack(float deltaTime)
{
	// �y�f�o�b�O�p�z
	//UE_LOG(LogTemp, Log, TEXT("Invoke PoliceAttack()"));

	// NULL�`�F�b�N	
	if (!EnemyBulletClass) { /*UE_LOG(LogTemp, Log, TEXT("Nothing EnemyBullet"));*/ return; }	// ��������e�����邩�ǂ����`�F�b�N
	if (!_owner) { /*UE_LOG(LogTemp, Log, TEXT("Failed To Acquire Owner"));*/ return;}		// �R���|�[�l���g�̃I�[�i�[�ł��� Actor �����邩�`�F�b�N

	// �o�ߎ��Ԃ̌v��
	_bulletTimer += deltaTime;

	// �N�[���^�C������
	if (!_hasFired) // �܂��e�𔭎˂��Ă��Ȃ��ꍇ
	{
		// �\���Ă����ԁi�\�������o���j
		if (_bulletTimer <= _timeToFire - _predictionStopToFireInterval)
		{
			// �\�������o��
			DrawPredictionSplineWithCollision(deltaTime);
			// �\������\���ɂ���
			if (!_pLineControllerComponent) { /*UE_LOG(LogTemp, Warning, TEXT("Not _pLineControllerComponent")); */return; }
			_pLineControllerComponent->DisplayPredictionLineActor();
		}
		// �ł��������܂��Ă��ė\�����������鎞��
		else if (_timeToFire - _predictionStopToFireInterval <= _bulletTimer)
		{
			// �\�������\���ɂ���
			if (!_pLineControllerComponent) {/* UE_LOG(LogTemp, Warning, TEXT("Not _pLineControllerComponent"));*/ return; }
			_pLineControllerComponent->HidePredictionLineActor();
		}
		// �e��ł�
		if (_timeToFire <= _bulletTimer)
		{
			SpawnBullet();         // �e�𔭎�
			_hasFired = true;      // ���˃t���O�𗧂Ă�
			_bulletTimer = 0.0f;   // �^�C�}�[�����Z�b�g
		}
	}
	else // ���ˌ�̃N�[���^�C�����v��
	{
		if (_enemyAttackCooldown <= _bulletTimer)
		{
			_bulletTimer = 0.0f;   // �N�[���_�E���I���A�^�C�}�[�����Z�b�g
			_hasFired = false;     // �Ăє��ˉ\�ɂ���
		}
	}
}

// �֐����FDrawPredictionSplineWithCollision
// �����F�P�t���[���ɂ����鎞��
// �߂�l�F�Ȃ�
// ���e�F�����̈ʒu����L���X�g����
void UHelicopterAttackComponent::DrawPredictionSplineWithCollision(float deltaTime)
{
	if (!_pLineControllerComponent) { /*UE_LOG(LogTemp, Warning, TEXT("Not _pLineControllerComponent"));*/ return; }
	if (!_playerActor) { /*UE_LOG(LogTemp, Warning, TEXT("Not Find Player"));*/ return; }

	// �w���̈ʒu�ƌ����Ă���������擾
	_startPointToDrawPrediction = _owner->GetActorLocation();  // ���_�̈ʒu
	FRotator _rotation = _owner->GetActorRotation();  // ���_�̉�]
	FVector _forwardDirection = _rotation.Vector();  // �����Ă�������̃x�N�g��

	// �����΂��������w��
	_endPointToDrawPrediction = _playerActor->GetActorLocation();	// �I�_�̈ʒu

	// �Փ˔���
	FHitResult HitResult;

	// Line Trace ���s
	bool bHit = GetWorld()->LineTraceSingleByObjectType(HitResult, _startPointToDrawPrediction, _endPointToDrawPrediction, FCollisionObjectQueryParams::AllObjects, _queryParamsToTrace);
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
			_endPointToDrawPrediction = HitResult.Location;

			// �␳��End�̍��W��Start���傫���Ȃ�����␳
			if (_startPointToDrawPrediction.X <= _endPointToDrawPrediction.X)
			{
				_endPointToDrawPrediction = _startPointToDrawPrediction;
			}
		}

		// �Փ˂���Actor��\��
		//UE_LOG(LogTemp, Log, TEXT("Hit Actor: %s"), *HitActor->GetName());
	}
	else
	{
		// �Փ˂��Ȃ������ꍇ
		//UE_LOG(LogTemp, Log, TEXT("No hit"));
	}

	// �f�o�b�O���C
	//DrawDebugLine(GetWorld(), _startPointToDrawPrediction, _endPointToDrawPrediction, FColor::Green, false, 1.0f, 0, 1.0f);
	// �f�o�b�O�p
	//UE_LOG(LogTemp, Log, TEXT("PoliceAttackComopnent Start: %s, End: %s"), *Start.ToString(), *End.ToString());

	// �\�����̍X�V
	_pLineControllerComponent->UpdateLineActor(_startPointToDrawPrediction, _endPointToDrawPrediction);

	// �w������v���C���[�ւ̕����x�N�g�����擾�i�n�_�F�w���̍��W�A�I�_�F�v���C���[�̍��W�j
	_rotationToFire = CalculateRotationByPoints(_owner->GetActorLocation(), _playerActor->GetActorLocation());
}

// �֐����FCalculateRotationByPoints
// �����F�n�_�̍��W, �I�_�̍��W
// �߂�l�F�w������v���C���[�ւ̕����x�N�g��
// ���e�F�n���ꂽ�n�_����I�_�ւ̕����x�N�g�����v�Z����֐�
FRotator UHelicopterAttackComponent::CalculateRotationByPoints(const FVector& startPoint, const FVector& endPoint)
{
	// �����x�N�g�����v�Z
	FVector Direction = endPoint - startPoint;
	// ���K�����ĒP�ʃx�N�g���ɕϊ�
	FVector NormalizedDirection = Direction.GetSafeNormal();
	// FRotator���擾
	FRotator Rotation = NormalizedDirection.Rotation();

	return Rotation;
}

// �֐����FSpawnBullet
// �����F�Ȃ�
// �߂�l�F�Ȃ�
// ���e�F�e���C���X�^���X������֐�
void UHelicopterAttackComponent::SpawnBullet()
{
	if (!_playerActor) { /*UE_LOG(LogTemp, Warning, TEXT("Not Find Player"));*/ return; }

	// ���ˈʒu������i�w���̈ʒu + �w���������Ă������(�P�ʃx�N�g��) * _enemyBulletOffset�j
	FVector SpawnLocation = _owner->GetActorLocation() + _owner->GetActorForwardVector() * _enemyBulletOffset;

	// EnemyBullet �𐶐�
	AEnemyBullet* _spawnedEnemyBullet = GetWorld()->SpawnActor<AEnemyBullet>(EnemyBulletClass, SpawnLocation, _rotationToFire);
	if (_spawnedEnemyBullet)
	{
		_spawnedEnemyBullet->SetDirection(_rotationToFire.Vector());
		_spawnedEnemyBullet->SetBulletSpeed(_bulletSpeed);
		_spawnedEnemyBullet->SetOwner(_owner);
	}	
}

// �֐����F_setMoveTargetActor
// �����F�Ȃ�
// �߂�l�F�Ȃ�
// ���e�F�w���R�v�^�[�̈ړ��ڕW�̃^�[�Q�b�g��ݒ肷��֐�
void UHelicopterAttackComponent::_setMoveTargetActor()
{
	// �ړ��ڕW�A�N�^�[��ݒ�
	switch (_moveTargetNumber)
	{
	// �E��
	case 1:
		if (_moveTargetActors)
		{
			_moveTargetActor = _moveTargetActors[0];
		}
		//else
		//{
		//	// �f�o�b�O�p
		//	//UE_LOG(LogTemp, Warning, TEXT("_moveTargetActors[0] do not set"));
		//}
		break;
	// ����
	case 2:
		if (_moveTargetActors[1])
		{
			_moveTargetActor = _moveTargetActors[1];
		}
		//else
		//{
		//	// �f�o�b�O�p
		//	UE_LOG(LogTemp, Warning, TEXT("_moveTargetActors[1] do not set"));
		//}
		break;
	// ����
	case 3:
		if (_moveTargetActors[2])
		{
			_moveTargetActor = _moveTargetActors[2];
			// �������ɂ���
			// ��]�l���w��
			FRotator NewRotation = FRotator(0.0f, 0.0f, 180.0f);
			// �A�N�^�[�̉�]��ݒ�
			_owner->SetActorRotation(NewRotation);
		}
		//else
		//{
		//	// �f�o�b�O�p
		//	UE_LOG(LogTemp, Warning, TEXT("_moveTargetActors[2] do not set"));
		//}
		break;
	default:
		// �f�o�b�O�p
		//UE_LOG(LogTemp, Warning, TEXT("Do not set _moveTargetActors"));
		break;
	}
}

// �Ë�����
void UHelicopterAttackComponent::SetMoveTargetNumber(int moveTargetNumber)
{
	UE_LOG(LogTemp, Log, TEXT("Invoke SetMoveTargetNumber"));
	// �ړ��ڕW�A�N�^�[��ݒ�
	switch (moveTargetNumber)
	{
		// �E��
	case 1:
		_moveTargetNumber = 1;
		//UE_LOG(LogTemp, Log, TEXT("MoveTargetNumber is Right"));// �f�o�b�O�p
		break;
		// ����
	case 2:
		_moveTargetNumber = 2;
		//UE_LOG(LogTemp, Log, TEXT("MoveTargetNumber is Center"));// �f�o�b�O�p
		break;
		// ����
	case 3:
		_moveTargetNumber = 3;
		//UE_LOG(LogTemp, Log, TEXT("MoveTargetNumber is Left"));// �f�o�b�O�p
		break;
	default:
		//UE_LOG(LogTemp, Log, TEXT("MoveTargetNumber is None"));	// �f�o�b�O�p
		break;
	}
}