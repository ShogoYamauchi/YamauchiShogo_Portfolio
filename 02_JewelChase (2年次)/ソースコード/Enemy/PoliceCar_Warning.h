//--------------------------------------------------------------------
// �t�@�C�����FPoliceCar_Warning.h
// �T�v�@�@�@�F�p�g�J�[�̌x���}�[�N�𐧌䂷��N���X
// �쐬�ҁ@�@�F�R���@����
// �X�V���e�@�F2025/01/25	�N���X�̍쐬 
//--------------------------------------------------------------------

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PoliceCar_Warning.generated.h"

UCLASS()
class PROTOTYPE_API APoliceCar_Warning : public AActor
{
	GENERATED_BODY()

protected:
	// �Q�[���X�^�[�g���A�܂��͐������ɌĂ΂�鏈��
	virtual void BeginPlay() override;

public:
	// �R���X�g���N�^
	APoliceCar_Warning();
	// ���t���[������
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float OpacityValue;	// �I�p�V�e�B�̒l

private:
	UPROPERTY(EditAnywhere)
	float _opacityMaxValue;		// �����x�̍ő�l
	UPROPERTY(EditAnywhere)
	float _opacityMinValue;		// �����x�̍ŏ��l
	UPROPERTY(EditAnywhere)
	float _destroyTime;	// �X�|�[�����Ă�����ł���܂ł̎���
	UPROPERTY(EditAnywhere)
	float _cycleDuration;	// ���̓_�łɂ����鎞��

	UPROPERTY(EditAnywhere)
	int32 _blinkingMaxCount;		// �_�ł��s��(�����łP)��

	float _midPoint;	// �����x�̍ő�l�ƍŏ��l�̒��S�l
	float _amplitude;	// �����x�̐U�ꕝ
	float _timer;	// �o�ߎ��ԑ���p
	int32 _blinkingCurrentCount;	// ���݂̓_�ŉ�
	bool _isBlinking;	// �_�ł������邩�ǂ����̃t���O

	void _updateBlinking();	// �����x�����炩�ɑ���������֐�
};