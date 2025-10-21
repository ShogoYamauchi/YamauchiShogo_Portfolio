//--------------------------------------------------------------------
// �t�@�C�����FEnemyBullet.h
// �T�v�@�@�@�F�G�̒e�N���X
// �쐬�ҁ@�@�F�R���@����
// �X�V���e�@�F2024/12/08	�N���X�̍쐬
//--------------------------------------------------------------------

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "prototype/Interface/IMovement.h"
#include "EnemyBullet.generated.h"

// �O���錾
class UStaticMeshComponent;
class UEnemyBullet;
class UProjectileMovementComponent;
class USphereComponent;

class AEnemy;

UCLASS()
class PROTOTYPE_API AEnemyBullet : public AActor
{
	GENERATED_BODY()

protected:
	// �Q�[���X�^�[�g���A�܂��͐������ɌĂ΂�鏈��
	virtual void BeginPlay() override;

public:
	// �R���X�g���N�^
	AEnemyBullet();
	// ���t���[������
	virtual void Tick(float DeltaTime) override;

	// �Փ˂��n�߂����ɌĂяo���֐��i�����I�ڐG�͖����j
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// �i�ޕ�����ݒ肷��֐�
	void SetDirection(FVector direction);
	// �e�̃X�s�[�h��ݒ肷��֐�
	void SetBulletSpeed(float _bulletSpeed);

private:
	UPROPERTY(EditAnywhere)
	float _timeToDisappear;
	UPROPERTY()
	USphereComponent* _pSphereComponent;	// �X�t�B�A�R���W�����R���|�[�l���g

	FVector _direction;		// �e����ԕ���
	float _moveSpeed;	// �e�̃X�s�[�h
	float _timer;	// �^�C�}�[
};
