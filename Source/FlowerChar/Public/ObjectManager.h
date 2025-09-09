// 오브젝트 저장하고 있는 오브젝트 매니저

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

	
	//공통으로 사용하는 오브젝트 가져오기
	void PutCommonMesh();


	//따로 이 오브젝트 매니저에 경로로 지정된 오브젝트 가져오기
	void PutPollingMesh();


	//가져오되, 풀링되지는 않는 메쉬 가져오기
	//생성자에서 직접 초기화는 X
	void PutNonPollingMesh();


	//Mesh를 가져옴 - Common
	//예상되는 이슈 -> 메모리 관리
	UStaticMesh* GetCommonMesh(FString name);

	//mesh를 가져옴 - Polling
	UStaticMesh* GetPollingMesh(FString name);

	UStaticMesh* GetNonPollingMesh(FString name);


public:
	
	//기본적으로 들어가는 오브젝트 

	//전체 모든 변수에 대해서
	//string : 이름
	//StaticMesh : 오브젝트입니다.
	UPROPERTY(VisibleAnywhere, Category = "Common-Polling")
	TMap<FString, UStaticMesh*> CommonObject;

	//스테이지/씬마다 다르게 가지고 있는 오브젝트. 기본적으로 풀링되어 스폰되어 있음.
	UPROPERTY(VisibleAnywhere, Category = "Polling")
	TMap<FString, UStaticMesh*> PollingObject;
	//경로
	UPROPERTY(EditAnywhere, Category = "Polling")
	TMap<FString, UStaticMesh*> PollingObjectPath; // 경로

	//스테이지/씬마다 가지고는 있으나 Non-Polling되는 오브젝트들.
	UPROPERTY(VisibleAnywhere, Category = "Non-Polling")
	TMap<FString, UStaticMesh*> NonPollingObject;
	UPROPERTY(EditAnywhere, Category = "Non-Polling")
	TMap<FString, UStaticMesh*> NonPollingObjectPath;
};
