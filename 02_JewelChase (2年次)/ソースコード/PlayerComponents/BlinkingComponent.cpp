//--------------------------------------------------------------------
// �t�@�C�����FBlinkingComponent.cpp
// �T�v�@�@�@�F�_�ł��邽�߂̃R���|�[�l���g
// �쐬�ҁ@�@�F�R���@����
// �X�V���e�@�F2025/1/10	�N���X�̍쐬
//--------------------------------------------------------------------

#include "BlinkingComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"

// �R���X�g���N�^
UBlinkingComponent::UBlinkingComponent()
	: OpacityValue(1.0f)
	, _midPoint(0.0f)
	, _isBlinking(false)
{
    // ���t���[���A���̃N���X��Tick()���ĂԂ��ǂ��������߂�t���O
    // �K�v�ɉ����āA�p�t�H�[�}���X����̂��߂ɐ؂邱�Ƃ��ł���B
    PrimaryComponentTick.bCanEverTick = true;
}

// �Q�[���X�^�[�g���A�܂��͐������ɌĂ΂�鏈��
void UBlinkingComponent::BeginPlay()
{
    Super::BeginPlay();

	// �l�̑����ɂ����ĕK�v�Ȑ��l�̌v�Z
	_midPoint = (_opacityMaxValue + _opacityMinValue) / 2.0f;	// �����x�̍ő�l�ƍŏ��l�̒��S�l
	_amplitude = (_opacityMaxValue - _opacityMinValue) / 2.0f;	// �����x�̐U�ꕝ 
}

// ���t���[������
void UBlinkingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// �t���O���オ��܂œ_�ł�����
	if (_isBlinking)
	{
		_updateBlinking(DeltaTime);
	}
	else
	{
		_timer = 0.0f;
	}
}

// �֐����FTriggerBlinking
// �����F�_�łɂ�����S�̂̎��� float�^
// �߂�l�F�Ȃ�
// ���e�F�_�ł̃g���K�[��ON�ɂ���֐�(����������n���΂��̓n���ꂽ���ԕ��_�ł�����) 
void UBlinkingComponent::TriggerBlinking(float blinkDuration)
{
	// �_�ŊJ�n
	_isBlinking = true;
	_blinkDuration = blinkDuration;
}


// �֐����F_updateBlinking
// �����F�P�t���[���ɂ����鎞��
// �߂�l�F�Ȃ�
// �����x�𑝌�������֐�
void UBlinkingComponent::_updateBlinking(float _deltaTime)
{
	// �t���O���o���Ă��Ȃ��ꍇ�������Ȃ�
	if (!_isBlinking) return;

	// �o�ߎ��Ԍv��
	_timer += _deltaTime; // 1�t���[�����ƂɎ��Ԃ�i�߂�

	// �c��_�Ŏ��Ԃɉ����ē_�ŊԊu�𑬂߂邽�߂̕ϐ����v�Z
	float _remainingTime = _blinkDuration - _timer;	// �c�莞��
	float _blinkingSpeed = FMath::Clamp(1.0f / _remainingTime, _blinkMinSpeed, _blinkMaxSpeed); // �w�肵���͈͓��œ_�ŃX�s�[�h�𑝂₷
	// �_�ł̐i�s�x���v�Z
	float _progressCycle = FMath::Fmod(_timer * _blinkingSpeed, 1.0f);

	// Sin�J�[�u���g�����l�̑���
	OpacityValue = _amplitude * FMath::Sin(2.0f * PI * _progressCycle) + _midPoint;

	// �_�Ŏ��Ԃ��I�������ꍇ�A�_�ł��~���ĕs�����ɐݒ�
	if (_timer >= _blinkDuration)
	{
		_isBlinking = false;  // �_�ł��~
		OpacityValue = 1.0f;  // ���S�ɕs�����ɂ���
	}

	// �f�o�b�O�p
	//UE_LOG(LogTemp, Log, TEXT("_progressInCycle: %f"), _progressInCycle);
	//UE_LOG(LogTemp, Log, TEXT("Current Value: %f"), OpacityValue);
}