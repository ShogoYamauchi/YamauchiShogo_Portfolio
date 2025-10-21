//--------------------------------------------------------------------
// �t�@�C�����FEnemy.cpp
// �T�v�@�@�@�F�G�i�G�ɑ΂��ă_���[�W��^������́j�̍����N���X
// �쐬�ҁ@�@�F�R���@����
// �X�V���e�@�F2024/11/25	Enemy�N���X�̍쐬
//--------------------------------------------------------------------

#include "Enemy.h"
#include "EnemyAttackComponent.h"
#include "EnemyDamagedComponent.h"
#include "EnemyDeadComponent.h"
#include "prototype/Player/PlayerBullet.h"

// �R���X�g���N�^
AEnemy::AEnemy()
	: _hp(0)
	, _pAttackComponent(nullptr)
	, _pDamagedComponent(nullptr)
	, _pDeadComponent(nullptr)
{
	// ���t���[���A���̃N���X��Tick()���ĂԂ��ǂ��������߂�t���O
	// �K�v�ɉ����āA�p�t�H�[�}���X����̂��߂ɐ؂邱�Ƃ��ł���B
	PrimaryActorTick.bCanEverTick = true;

	_pAttackComponent = CreateDefaultSubobject<UEnemyAttackComponent>(TEXT("_pAttackComponent"));		// �U�����邽�߂̃R���|�[�l���g
	//_pDamagedComponent = CreateDefaultSubobject<UEnemyDamagedComponent>(TEXT("_pDamagedComponent"));	// �_���[�W���󂯂邽�߂̃R���|�[�l���g
	//_pDeadComponent = CreateDefaultSubobject<UEnemyDeadComponent>(TEXT("_pDeadComponent"));				// ���ʂ��߂̃R���|�[�l���g
}

// �Q�[���X�^�[�g���A�܂��͐������ɌĂ΂�鏈��
void AEnemy::BeginPlay()
{
	Super::BeginPlay();	

	// �A�N�^�[�ɂ��Ă��� UPrimitiveComponent ���擾
	GetComponents<UPrimitiveComponent>(_pCollisionComponent);
	for (int32 i = _pCollisionComponent.Num() - 1; i >= 0; i--)
	{
		if (!_pCollisionComponent[i]->GetCollisionEnabled() || !_pCollisionComponent[i]->GetGenerateOverlapEvents())
		{
			_pCollisionComponent.RemoveAt(i); // �R���W���������ȃR���|�[�l���g�����O
		}
	}
	//UE_LOG(LogTemp, Log, TEXT("Found %d valid collision components"), _pCollisionComponent.Num());	// �f�o�b�O�p
	for (UPrimitiveComponent* Comp : _pCollisionComponent)
	{
		//UE_LOG(LogTemp, Log, TEXT("Valid Collision Component: %s"), *Comp->GetName());	// �f�o�b�O�p
		// �I�[�o�[���b�v�Ƀo�C���h����
		Comp->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::OnOverlapBegin);
	}

	FRotator(0.0f, 0.0f, 180.0f); // Z �� 180 �x��]
}

// ���t���[������
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// �U�������𖈃t���[���Ăяo��
	if (_pAttackComponent != nullptr)
	{
		// �U���\���H
		if (_pAttackComponent->CanAttack())
		{
			_pAttackComponent->EnemyAttack(DeltaTime); //UE_LOG(LogTemp, Log, TEXT("_pAttackComponent"));
		}
	}	
}

// �֐����FOnBeiginOverLap
// �����F��ɋL��
// �߂�l�F�Ȃ�
// ���e�F��������ɓ��������u�ԂɌĂяo�����֐�
void AEnemy::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// �y�f�o�b�O�p�z
	//UE_LOG(LogTemp, Log, TEXT("Enemy hit something"))
	//UE_LOG(LogTemp, Log, TEXT("Hit Actor is %s"), *OtherActor->GetName());	

	//// �f�o�b�O�p
	//if (OtherActor->ActorHasTag("Oil_Explosion"))
	//{
	//	UE_LOG(LogTemp, Log, TEXT("Hit Oil_Explosion"));
	//}

	// ���������A�N�^�[�̃^�O���v���C���[�̋��Ȃ珈��
	if (OtherActor->ActorHasTag("PlayerBullet"))
	{
		//UE_LOG(LogTemp, Log, TEXT("Hit Oil_Explosion")); // �f�o�b�O�p
		if (IsValid(OtherActor))
		{
			APlayerBullet* PlayerBullet = Cast<APlayerBullet>(OtherActor);
			if (IsValid(PlayerBullet))
			{
				_hp -= PlayerBullet->GetBulletAttack();
				//UE_LOG(LogTemp, Log, TEXT("HP %i"),_hp);   // �f�o�b�O�p(���ꗎ����)
			}		
		}
	}
}

// �f�o�b�O�p
//void AEnemy::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
//	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
//{
//	// �f�o�b�O�p
//	if (OtherActor->ActorHasTag("Oil_Explosion"))
//	{
//		UE_LOG(LogTemp, Log, TEXT("HitEnd Oil_Explosion"));
//	}
//}