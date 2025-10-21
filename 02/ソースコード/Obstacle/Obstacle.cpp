//--------------------------------------------------------------------
// �t�@�C�����FObstacle.cpp
// �T�v�@�@�@�F��Q���̊��N���X
// �쐬�ҁ@�@�F�R���@����
// �X�V���e�@�F2024/01/30	�N���X�̍쐬
//--------------------------------------------------------------------

#include "prototype/Obstacle/Obstacle.h"
#include "prototype/Player/PlayerBullet.h"
#include "Components/BoxComponent.h"

// �R���X�g���N�^
AObstacle::AObstacle()
{
	// ���t���[���A���̃N���X��Tick()���ĂԂ��ǂ��������߂�t���O
	// �K�v�ɉ����āA�p�t�H�[�}���X����̂��߂ɐ؂邱�Ƃ��ł���B
	PrimaryActorTick.bCanEverTick = true;

	//// �J�v�Z���R���W�����ɃI�[�o�[���b�v��ݒ�
	//if (_pBoxComponent)
	//{
	//	_pBoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AEnemy::OnOverlapBegin);
	//}
}

// �Q�[���X�^�[�g���A�܂��͐������ɌĂ΂�鏈��
void AObstacle::BeginPlay()
{
	Super::BeginPlay();

	// �R���W�����R���|�[�l���g���I�[�o�[���b�v�ɐݒ�
	//_CollisionComponentsToOverlap->OnComponentBeginOverlap.AddDynamic(this, &AObstacle::OnOverlapBegin);
}

// ���t���[������
void AObstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// �֐����FOnBeiginOverLap
// �����F��ɋL��
// �߂�l�F�Ȃ�
// ���e�F��������ɓ��������u�ԂɌĂяo�����֐�
void AObstacle::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// �y�f�o�b�O�p�z
	//UE_LOG(LogTemp, Log, TEXT("Obstacle hit something"))

	//���������A�N�^�[�̃^�O���v���C���[�̋��Ȃ珈��
	if (OtherActor->ActorHasTag("PlayerBullet"))
	{
		if (IsValid(OtherActor))
		{
			APlayerBullet* PlayerBullet = Cast<APlayerBullet>(OtherActor);
			Hp -= PlayerBullet->GetBulletAttack();
		}
	}
}


