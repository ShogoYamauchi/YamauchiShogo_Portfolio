//--------------------------------------------------------------------
// �t�@�C�����FEnemyBullet.cpp
// �T�v�@�@�@�F�G�̒e�N���X
// �쐬�ҁ@�@�F�R���@����
// �X�V���e�@�F2024/12/08	�N���X�̍쐬
//--------------------------------------------------------------------

#include "EnemyBullet.h"
#include "Enemy.h"
#include "Components/SphereComponent.h"

// �R���X�g���N�^
AEnemyBullet::AEnemyBullet()
	: _timer(0.0f)
{
    // ���t���[���A���̃N���X��Tick()���ĂԂ��ǂ��������߂�t���O
    // �K�v�ɉ����āA�p�t�H�[�}���X����̂��߂ɐ؂邱�Ƃ��ł���B
	PrimaryActorTick.bCanEverTick = true;
}

// �Q�[���X�^�[�g���A�܂��͐������ɌĂ΂�鏈��
void AEnemyBullet::BeginPlay()
{
	Super::BeginPlay();	

	// �I�[�o�[���b�v�p�̃R���|�[�l���g���擾
	_pSphereComponent = FindComponentByClass<USphereComponent>();

	if (_pSphereComponent)
	{
		// �X�t�B�A�R���W�����ɃI�[�o�[���b�v��ݒ�
		_pSphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AEnemyBullet::OnOverlapBegin);
	}
	else
	{
		// �f�o�b�O�p
		//UE_LOG(LogTemp, Warning, TEXT("No _pSphereComponent"))
	}
}

// ���t���[������
void AEnemyBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// ���ԑ���
	_timer += DeltaTime;

	// �e���w�肵�������ɔ�΂�
	SetActorLocation(this->GetActorLocation() + (_direction * _moveSpeed));

	// �w�肵�����Ԍo�߂��Ă������
	if (_timeToDisappear <= _timer)
	{
		this->Destroy();
	}
}

// �֐����FSetDirection
// �����F�i�ޕ���
// �߂�l�F�Ȃ�
// ���e�F�eEnemy����n���ꂽ������ݒ肷��֐�
void AEnemyBullet::SetDirection(FVector direction)
{
	// �i�ޕ����̐ݒ�
	_direction = direction;
}

// �e�̃X�s�[�h��ݒ肷��֐�
void AEnemyBullet::SetBulletSpeed(float _bulletSpeed)
{
	// �e�̃X�s�[�h��ݒ�
	_moveSpeed = _bulletSpeed;
}

// �֐����FOnBeiginOverLap
// �����F��ɋL��
// �߂�l�F�Ȃ�
// ���e�F��������ɓ��������u�ԂɌĂяo�����֐�
void AEnemyBullet::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{	
	// �f�o�b�O�p
	//UE_LOG(LogTemp, Log, TEXT("Hit Actor: %s"), OtherActor);
	
	// �I�[�i�[�ȊO�̃A�N�^�[�Ƃ̃I�[�o�[���b�v���m�F
	if (OtherActor != GetOwner() && !OtherActor->ActorHasTag("Item"))
	{
		this->Destroy();
		// �f�o�b�O�p
		//UE_LOG(LogTemp, Log, TEXT("EnemyBullet Destroy"));
	}
}

