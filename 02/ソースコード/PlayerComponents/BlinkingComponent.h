//--------------------------------------------------------------------
// �t�@�C�����FBlinkingComponent.h
// �T�v�@�@�@�F�_�ł��邽�߂̃R���|�[�l���g
// �쐬�ҁ@�@�F�R���@����
// �X�V���e�@�F2025/1/10	�N���X�̍쐬
//--------------------------------------------------------------------

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BlinkingComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROTOTYPE_API UBlinkingComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
    // �Q�[���X�^�[�g���A�܂��͐������ɌĂ΂�鏈��
    virtual void BeginPlay() override;

public:
    // �R���X�g���N�^
    UBlinkingComponent();
    // ���t���[������
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		float OpacityValue;	// �I�p�V�e�B�̒l

	void TriggerBlinking(float blinkDuration);	// �_�ł̃g���K�[��ON�ɂ���֐� 

private:
	UPROPERTY(EditAnywhere)
		float _opacityMaxValue;		// �����x�̍ő�l
	UPROPERTY(EditAnywhere)
		float _opacityMinValue;		// �����x�̍ŏ��l
	UPROPERTY(EditAnywhere)
		float _blinkMinSpeed;		// �_�ł̍Œx�X�s�[�h
	UPROPERTY(EditAnywhere)
		float _blinkMaxSpeed;		// �_�ł��ő��X�s�[�h
	UPROPERTY()
		float _blinkDuration;		// �_�ł��s���S�̂̎���

	float _midPoint;	// �����x�̍ő�l�ƍŏ��l�̒��S�l
	float _amplitude;	// �����x�̐U�ꕝ
	float _timer;	// �o�ߎ��ԑ���p
	bool _isBlinking;	// �_�ł������邩�ǂ����̃t���O

	void _updateBlinking(float _deltaTime);	// �����x�����炩�ɑ���������֐�
};
