// ������Ʈ �����ϰ� �ִ� ������Ʈ �Ŵ���

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ObjectManager.generated.h"

UCLASS()
class FLOWERCHAR_API AObjectManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AObjectManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	//�������� ����ϴ� ������Ʈ ��������
	void PutCommonMesh();


	//���� �� ������Ʈ �Ŵ����� ��η� ������ ������Ʈ ��������
	void PutPollingMesh();


	//��������, Ǯ�������� �ʴ� �޽� ��������
	//�����ڿ��� ���� �ʱ�ȭ�� X
	void PutNonPollingMesh();


	//Mesh�� ������ - Common
	//����Ǵ� �̽� -> �޸� ����
	UStaticMesh* GetCommonMesh(FString name);

	//mesh�� ������ - Polling
	UStaticMesh* GetPollingMesh(FString name);

	UStaticMesh* GetNonPollingMesh(FString name);


public:
	
	//�⺻������ ���� ������Ʈ 

	//��ü ��� ������ ���ؼ�
	//string : �̸�
	//StaticMesh : ������Ʈ�Դϴ�.
	UPROPERTY(VisibleAnywhere, Category = "Common-Polling")
	TMap<FString, UStaticMesh*> CommonObject;

	//��������/������ �ٸ��� ������ �ִ� ������Ʈ. �⺻������ Ǯ���Ǿ� �����Ǿ� ����.
	UPROPERTY(VisibleAnywhere, Category = "Polling")
	TMap<FString, UStaticMesh*> PollingObject;
	//���
	UPROPERTY(EditAnywhere, Category = "Polling")
	TMap<FString, UStaticMesh*> PollingObjectPath; // ���

	//��������/������ ������� ������ Non-Polling�Ǵ� ������Ʈ��.
	UPROPERTY(VisibleAnywhere, Category = "Non-Polling")
	TMap<FString, UStaticMesh*> NonPollingObject;
	UPROPERTY(EditAnywhere, Category = "Non-Polling")
	TMap<FString, UStaticMesh*> NonPollingObjectPath;
};
