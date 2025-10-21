
//--------------------------------------------------------------------
// �t�@�C�����FPredectionLine.cpp
// �T�v�@�@�@�F�\������Actor�N���X
// �쐬�ҁ@�@�F�R���@����
// �X�V���e�@�F2024/12/15	�N���X�̍쐬
//--------------------------------------------------------------------


#include "PredictionLine.h"
#include "Components/SplineComponent.h"
#include "Components/SplineMeshComponent.h"

// �R���X�g���N�^
APredictionLine::APredictionLine()
	: _pSplineMeshComponent(nullptr)
{
	// ���t���[���A���̃N���X��Tick()���ĂԂ��ǂ��������߂�t���O
	// �K�v�ɉ����āA�p�t�H�[�}���X����̂��߂ɐ؂邱�Ƃ��ł���B
	PrimaryActorTick.bCanEverTick = false;

	// Spline Component�̍쐬
	_pSplineComponent = CreateDefaultSubobject<USplineComponent>(TEXT("SplineComponent"));
	RootComponent = _pSplineComponent;
	_pSplineComponent->SetMobility(EComponentMobility::Movable);	// ���I�ɐݒ�
}

// �Q�[���X�^�[�g���A�܂��͐������ɌĂ΂�鏈��
void APredictionLine::BeginPlay()
{
	Super::BeginPlay();

	// �������̍��W��ݒ�
	_pSplineComponent->ClearSplinePoints(true);
	_pSplineComponent->AddSplinePoint(_splineStartPoint, ESplineCoordinateSpace::World, true);
	_pSplineComponent->AddSplinePoint(_splineEndPoint, ESplineCoordinateSpace::World, true);
	_pSplineComponent->UpdateSpline();
}

// �֐����FUpdateLine
// �����F����`�悷��ۂ� �n�_�A�I�_
// �߂�l�F�Ȃ�
// ���e�F���I�ɐ���`�悷��֐�
void APredictionLine::UpdateLine(const FVector& startPoint, const FVector& endPoint)
{
	if (!_pSplineComponent) { UE_LOG(LogTemp, Warning, TEXT("Not SplineComponent")); return; }
	if (!GetOwner()) { return; }
	// �f�o�b�O�p
	//UE_LOG(LogTemp, Log, TEXT("hennkougomae�@StartPoint: %s, EndPoint: %s"), *StartPoint.ToString(), *EndPoint.ToString());
	//UE_LOG(LogTemp, Log, TEXT("Draw Line"));

	// ���W���X�V
	_splineStartPoint = startPoint;
	_splineEndPoint = endPoint;

	// ���łɃX�v���C�����b�V��������ꍇ�O�̃X�v���C�����b�V������
	if (IsValid(_pSplineMeshComponent))
	{
		// �R���|�[�l���g���폜
		_pSplineMeshComponent->UnregisterComponent();	 // �R���|�[�l���g�̓o�^����
		_pSplineMeshComponent->DestroyComponent();      // �R���|�[�l���g�̔j��

		// �|�C���^��nullptr�ɐݒ�
		_pSplineMeshComponent = nullptr;
	}

	// �X�v���C�����b�V���𐶐�
	USplineMeshComponent* _pNewSplineMesh = NewObject<USplineMeshComponent>(this);
	_pNewSplineMesh->SetMobility(EComponentMobility::Movable);	// ���I�ɐݒ�
	_pNewSplineMesh->SetStaticMesh(LineStaticMesh);		// ���炩���ߐݒ肵�����b�V��
	_pNewSplineMesh->SetMaterial(0, LineMaterial);	// �g�p����}�e���A��
	_pNewSplineMesh->SetStartAndEnd(_splineStartPoint, FVector::ZeroVector, _splineEndPoint, FVector::ZeroVector, true);

	// �R���|�[�l���g��o�^
	_pNewSplineMesh->RegisterComponent();

	// �V�����X�v���C�����b�V������
	_pSplineMeshComponent = _pNewSplineMesh;

	// �f�o�b�O�p
	//UE_LOG(LogTemp, Log, TEXT("Prediction StartPoint: %s, EndPoint: %s"), *StartPoint.ToString(), *EndPoint.ToString());
}


