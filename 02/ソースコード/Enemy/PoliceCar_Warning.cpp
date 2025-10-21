//--------------------------------------------------------------------
// �t�@�C�����FPoliceCar_Warning.cpp
// �T�v�@�@�@�F�p�g�J�[�̌x���}�[�N�𐧌䂷��N���X
// �쐬�ҁ@�@�F�R���@����
// �X�V���e�@�F2025/01/25	�N���X�̍쐬 
//--------------------------------------------------------------------

#include "PoliceCar_Warning.h"

// �R���X�g���N�^
APoliceCar_Warning::APoliceCar_Warning()
	: OpacityValue(0.0f)
	, _destroyTime(0.0f)
	, _midPoint(0.0f)
	, _amplitude(0.0f)
	, _timer(0.0f)
	, _blinkingCurrentCount(0)
	, _isBlinking(true)
{
	// ���t���[���A���̃N���X��Tick()���ĂԂ��ǂ��������߂�t���O
	// �K�v�ɉ����āA�p�t�H�[�}���X����̂��߂ɐ؂邱�Ƃ��ł���B
	PrimaryActorTick.bCanEverTick = true;
}

// �Q�[���X�^�[�g���A�܂��͐������ɌĂ΂�鏈��
void APoliceCar_Warning::BeginPlay()
{
	Super::BeginPlay();	

	// �l�̑����ɂ����ĕK�v�Ȑ��l�̌v�Z
	_midPoint = (_opacityMaxValue + _opacityMinValue) / 2.0f;	// �����x�̍ő�l�ƍŏ��l�̒��S�l
	_amplitude = (_opacityMaxValue - _opacityMinValue) / 2.0f;	// �����x�̐U�ꕝ 
}

// ���t���[������
void APoliceCar_Warning::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// ���ԑ���
	_timer += DeltaTime;

	// �t���O���オ��܂œ_�ł�����
	if (_isBlinking)
	{
		_updateBlinking();
	}
	else
	{
		this->Destroy();
	}
}

// �֐����F_updateBlinking
// �����F�Ȃ�
// �߂�l�F�Ȃ�
// �����x�����炩�ɑ���������֐�
void APoliceCar_Warning::_updateBlinking()
{
	// �i�s�x�𐳋K������
	float _progressInCycle = FMath::Fmod(_timer, _cycleDuration) / _cycleDuration;

	// Sin�J�[�u���g�����l�̑���
	OpacityValue =_amplitude * FMath::Sin(2.0f * PI * _progressInCycle) + _midPoint;

	// �����x��0.0f�߂��̒l�ɂȂ����ꍇ�A�T�C�N����i�ߓ_�ł��~�߂�
	if (OpacityValue <= 0.0001f)
	{
		_blinkingCurrentCount++;  // �_�ŉ񐔂��J�E���g
		//UE_LOG(LogTemp, Warning, TEXT("_blinkingCurrentCount: %i"), _blinkingCurrentCount);

		// �_�ŉ񐔂��B�����ꍇ,�_�Œ�~
		if (_blinkingMaxCount <= _blinkingCurrentCount)
		{
			_isBlinking = false; // �_�Œ�~
		}
	}

	// �f�o�b�O�p
	//UE_LOG(LogTemp, Log, TEXT("_progressInCycle: %f"), _progressInCycle);
	//UE_LOG(LogTemp, Log, TEXT("Current Value: %f"), OpacityValue);
}

