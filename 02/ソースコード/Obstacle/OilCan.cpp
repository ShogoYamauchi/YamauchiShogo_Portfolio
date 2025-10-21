//--------------------------------------------------------------------
// �t�@�C�����FOilCan.cpp
// �T�v�@�@�@�F�I�C���ʃN���X
// �쐬�ҁ@�@�F�R���@����
// �X�V���e�@�F2024/01/30	�N���X�̍쐬
//--------------------------------------------------------------------

#include "prototype/Obstacle/OilCan.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"

// �R���X�g���N�^
AOilCan::AOilCan()
{
	// ���t���[���A���̃N���X��Tick()���ĂԂ��ǂ��������߂�t���O
	// �K�v�ɉ����āA�p�t�H�[�}���X����̂��߂ɐ؂邱�Ƃ��ł���B
	PrimaryActorTick.bCanEverTick = true;

	// �R���|�[�l���g�𐶐�����	
	_pCapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));	// �J�v�Z���R���W�����i�����蔻��p�j
}

// �Q�[���X�^�[�g���A�܂��͐������ɌĂ΂�鏈��
void AOilCan::BeginPlay()
{
	Super::BeginPlay();

	// �J�v�Z���R���W����������ɍ쐬���ꂽ���m�F
	if (_pCapsuleComponent)
	{
		// �X�t�B�A�R���|�[�l���g��e�A�N�^�[��RootComponent�ɃA�^�b�`
		//_pCapsuleComponent->SetupAttachment(RootComponent);
		// �I�[�o�[���b�v�Ƀo�C���h����R���W�����R���|�[�l���g�z��ɒǉ�
		_CollisionComponentsToOverlap = Cast<UPrimitiveComponent>(_pCapsuleComponent);
	}
	else
	{
		// �f�o�b�O�p
		//UE_LOG(LogTemp, Warning, TEXT("No oil can _pCapsuleComponent"))
	}

	//�Ë�����
	_pSphereComponent = FindComponentByClass<USphereComponent>();
	if (_pSphereComponent)
	{
		// �f�o�b�O�p �@�I�[�o�[���b�v�Ƀo�C���h����
		//_pSphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AOilCan::OnOverlapBegin);
		// �R���W��������𖳌��ɂ���
		_pSphereComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		UE_LOG(LogTemp, Warning, TEXT("Sphere Component found"));
	}
	else
	{
		// �f�o�b�O�p
		UE_LOG(LogTemp, Warning, TEXT("Shere Component do not find"));
	}
}

// ���t���[������
void AOilCan::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// �Ë�����
	// �e�A�N�^�[�̈ʒu�Ɋ�Â��Ďq�R���|�[�l���g�̈ʒu���X�V
	if (_pSphereComponent)
	{
		_pSphereComponent->SetWorldLocation(RootComponent->GetComponentLocation());
	}
}

// �֐����FOnBeiginOverLap
// �����F��ɋL��
// �߂�l�F�Ȃ�
// ���e�F��������ɓ��������u�ԂɌĂяo�����֐�
void AOilCan::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// �f�o�b�O�p
	//UE_LOG(LogTemp, Log, TEXT("OilCan hit something"));
	//UE_LOG(LogTemp, Log, TEXT("Hit Actor is %s"), *OtherActor->GetName());	

	//���������A�N�^�[�̃^�O���v���C���[�̋��Ȃ珈��
	if (OtherActor->ActorHasTag("PlayerBullet"))
	{
		// ���N���X�̃I�[�o�[���b�v������
		AObstacle::OnOverlapBegin(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	}
}

// �֐����FTurnOnExplosionCollision
// �����F�Ȃ�
// �߂�l�F�Ȃ�
// ���e�F�����̃R���W������L���ɂ���֐�(Blueprint�Ăяo��)
void AOilCan::TurnOnExplosionCollision()
{
	// �R���W���������L���ɂ���
	if (_pSphereComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("_pSphereComponent is Active"));
		_pSphereComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	}
}



