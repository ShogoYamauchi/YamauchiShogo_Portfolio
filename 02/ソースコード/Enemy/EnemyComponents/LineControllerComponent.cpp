//--------------------------------------------------------------------
// �t�@�C�����FLineControllerComponent.cpp
// �T�v�@�@�@�F���`��A�N�^�[���g�����߂̃R���|�[�l���g�N���X
// �쐬�ҁ@�@�F�R���@����
// �X�V���e�@�F2024/12/15	�N���X�̍쐬
//--------------------------------------------------------------------

#include "LineControllerComponent.h"
#include "PredictionLine.h"

// �R���X�g���N�^
ULineControllerComponent::ULineControllerComponent()
{
	// ���t���[���A���̃N���X��Tick()���ĂԂ��ǂ��������߂�t���O
	// �K�v�ɉ����āA�p�t�H�[�}���X����̂��߂ɐ؂邱�Ƃ��ł���B
	PrimaryComponentTick.bCanEverTick = true;
}

// �Q�[���X�^�[�g���A�܂��͐������ɌĂ΂�鏈��
void ULineControllerComponent::BeginPlay()
{
	Super::BeginPlay();
}

// �Q�[���I�����A�܂��͔j�����ɌĂ΂�鏈��
void ULineControllerComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	// �I�[�i�[���j�������Ƃ��̂ݏ���
	if (EndPlayReason == EEndPlayReason::Destroyed)
	{
		// �c�����\������j��
		DestroyPredictionLineActor();

		// �f�o�b�O�m�F�p
		//UE_LOG(LogTemp, Log, TEXT("Destroy PridictionLineActor!"));
	}
}

// �֐����FUpdateLineActor
// �����F����`�悷��ۂ� �n�_�A�I�_
// �߂�l�F�Ȃ�
// ���e�F���I�ɐ���`�悷��֐�
void ULineControllerComponent::UpdateLineActor(FVector& Start, FVector& End)
{
	if (_predictionLineFlag) { return; }
	// �f�o�b�O�p
	//UE_LOG(LogTemp, Log, TEXT("StartPoint: %s, EndPoint: %s"), *Start.ToString(), *End.ToString());

	// ����`�悷��
	if (_pPredictionLineActor != nullptr)
	{
		_pPredictionLineActor->UpdateLine(Start, End);
	}
	else
	{
		// ���`��A�N�^�[���X�|�[�������ď�����
		SpawnAndInitializeLineActor();
	}
}

// �֐����FSpawnAndInitializeLineActor
// �����F�Ȃ�
// �߂�l�F�Ȃ�
// ���e�F�\���������x���ɔz�u�E���������s���֐�
void ULineControllerComponent::SpawnAndInitializeLineActor()
{
	if (!LineActorsClass)  // �X�|�[������A�N�^�[�N���X���ݒ肳��Ă��Ȃ��ꍇ�͉������Ȃ�
	{
		// �f�o�b�O�p
		//UE_LOG(LogTemp, Warning, TEXT("LineActorClass is not set!"));
		return;
	}

	// ���`��A�N�^�[���X�|�[��
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = GetOwner(); // ���̃R���|�[�l���g�����A�N�^�[�����L�҂Ƃ���
	FVector SpawnLocation = GetOwner()->GetActorLocation() + _lineOffset;	// �I�[�i�[�̍��W�ɃX�|�[��������
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;	// �X�|�[���ꏊ�ɉ��������Ă��X�|�[��������
	_pPredictionLineActor = GetWorld()->SpawnActor<APredictionLine>(LineActorsClass, SpawnLocation, FRotator::ZeroRotator, SpawnParams);

	// �f�o�b�O�p
	//if (_pPredictionLineActor)
	//{
	//	//UE_LOG(LogTemp, Log, TEXT("_pPredictionLineActor Actor: %s"));
	//}
	//else
	//{
	//	//UE_LOG(LogTemp, Error, TEXT("Failed to _pPredictionLineActor!"));
	//}
}

// �֐����FHidePredictionLineActor
// �����F�Ȃ�
// �߂�l�F�Ȃ�
// ���e�F�\�������\���ɂ���֐�
void ULineControllerComponent::HidePredictionLineActor()
{
	// _pPredictionLineActor �����݂����珈��
	if (_pPredictionLineActor)
	{
		// Actor���\���ɂ���
		_pPredictionLineActor->SetActorHiddenInGame(true);
	}
	else
	{
		// �f�o�b�O�p
		//UE_LOG(LogTemp, Error, TEXT("Failed to _pPredictionLineActor!"));
	}
}

// �֐����FDisplayPredictionLineActor
// �����F�Ȃ�
// �߂�l�F�Ȃ�
// ���e�F�\������\���ɂ���֐�
void ULineControllerComponent::DisplayPredictionLineActor()
{
	// _pPredictionLineActor �����݂����珈��
	if (_pPredictionLineActor)
	{
		// Actor��\���ɂ���
		_pPredictionLineActor->SetActorHiddenInGame(false);
	}
	//else
	//{
	//	// �f�o�b�O�p
	//	//UE_LOG(LogTemp, Error, TEXT("Failed to PredictionLineActor!"));
	//}
}

// �֐����FDestroyPredictionLineActor
// �����F�Ȃ�
// �߂�l�F�Ȃ�
// ���e�F�\�����̃A�N�^�[���폜����֐�
void ULineControllerComponent::DestroyPredictionLineActor()
{
	if (_pPredictionLineActor != nullptr) // LineActor���Ȃ������ꍇ�������Ȃ�
	{
		_pPredictionLineActor->Destroy();
	}
	//else
	//{
	//	UE_LOG(LogTemp, Warning, TEXT("Noting LineActorClass!"));
	//}
}