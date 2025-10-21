//--------------------------------------------------------------------
// �t�@�C�����FTrashCan.cpp
// �T�v�@�@�@�F�S�~���N���X
// �쐬�ҁ@�@�F�R���@����
// �X�V���e�@�F2024/02/12 �N���X�̍쐬
//--------------------------------------------------------------------

#include "prototype/Obstacle/TrashCan.h"
#include "prototype/Stage/StageManager.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

// �R���X�g���N�^
ATrashCan::ATrashCan()
	: DropItemValue(DropItems::Jewel_Blue)
{
	// ���t���[���A���̃N���X��Tick()���ĂԂ��ǂ��������߂�t���O
	// �K�v�ɉ����āA�p�t�H�[�}���X����̂��߂ɐ؂邱�Ƃ��ł���B
	PrimaryActorTick.bCanEverTick = true;

	// �R���|�[�l���g�𐶐�����	
	_pBoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("_pBoxComponent"));	// �J�v�Z���R���W�����i�����蔻��p�j
}

// �Q�[���X�^�[�g���A�܂��͐������ɌĂ΂�鏈��
void ATrashCan::BeginPlay()
{
	Super::BeginPlay();

	// �J�v�Z���R���W����������ɍ쐬���ꂽ���m�F
	if (_pBoxComponent)
	{
		// AObstacle �e�N���X�ɂ���I�[�o�[���b�v�p�R���W�����̔z��ɒǉ�
		_CollisionComponentsToOverlap = Cast<UPrimitiveComponent>(_pBoxComponent);
	}
	else
	{
		// �f�o�b�O�p
		//UE_LOG(LogTemp, Warning, TEXT("No oil can _pBoxComponent"))
	}
}

// �֐����FOnBeiginOverLap
// �����F��ɋL��
// �߂�l�F�Ȃ�
// ���e�F��������ɓ��������u�ԂɌĂяo�����֐�
void ATrashCan::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
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

// �֐����FSpawnDropItem
// �����F�Ȃ�
// �߂�l�F�Ȃ�
// ���e�F�A�C�e�����h���b�v������֐�
void ATrashCan::SpawnDropItem()
{
	// �X�|�[������ʒu�i���g�̈ʒu�j
	FVector SpawnLocation = GetActorLocation(); // ���g�̈ʒu���擾
	// �X�|�[���̉�]�i���̏ꍇ�̓A�C�e�������ʂ������悤�ɂ���j
	FRotator SpawnRotation = FRotator::ZeroRotator;
	// �X�|�[��������A�N�^�[�̕ϐ�
	AActor* SpawnedItem = nullptr;

	// eunm �^�ɑΉ������h���b�v�A�C�e����ݒ肷��
	if (DropItemValue == DropItems::Jewel_Blue)
	{
		// �W���G��
		SpawnedItem = GetWorld()->SpawnActor<AActor>(_pDropItems[0], SpawnLocation, SpawnRotation);
	}
	else if (DropItemValue == DropItems::Jewel_Red)
	{
		// �ԃW���G��
		SpawnedItem = GetWorld()->SpawnActor<AActor>(_pDropItems[0], SpawnLocation, SpawnRotation);
	}
	else if (DropItemValue == DropItems::Jewel_Yellow)
	{
		// ���W���G��
		SpawnedItem = GetWorld()->SpawnActor<AActor>(_pDropItems[0], SpawnLocation, SpawnRotation);
	}
	else if (DropItemValue == DropItems::Jewel_Purple)
	{
		// ���W���G��
		SpawnedItem = GetWorld()->SpawnActor<AActor>(_pDropItems[0], SpawnLocation, SpawnRotation);
	}
	else if (DropItemValue == DropItems::HpItem)
	{
		// �̗͉�
		SpawnedItem = GetWorld()->SpawnActor<AActor>(_pDropItems[0], SpawnLocation, SpawnRotation);
	}
	else if (DropItemValue == DropItems::Magnet)
	{
		// �}�O�l�b�g
		SpawnedItem = GetWorld()->SpawnActor<AActor>(_pDropItems[0], SpawnLocation, SpawnRotation);
	}
	else
	{
		// �f�o�b�O�p
		//UE_LOG(LogTemp, Warning, TEXT("do not set DropItemValue"));
	}

	// �Ë�����
	// �A�j���[�V������K�p
	if (SpawnedItem != nullptr)
	{
		//AStageManager�^�̃I�u�W�F�N�g��T���A�Ǘ�
		TSubclassOf<AStageManager> findClass;
		findClass = AStageManager::StaticClass();

		AActor* stageManager = UGameplayStatics::GetActorOfClass(GetWorld(), findClass);

		FName ItemTag = "Item";
		TArray<AActor*> Items;
		UGameplayStatics::GetAllActorsWithTag(GetWorld(), ItemTag, Items);

		Items.Push(SpawnedItem);

		if (stageManager)
		{
			Cast<AStageManager>(stageManager)->SetItems(Items);
		}
		else
		{
			// �f�o�b�O�p
			//UE_LOG(LogTemp, Warning, TEXT("No stageManager"));
		}
	}
}