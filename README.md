# MovementSync
MovementSync는 MMORPG 프로젝트 제작 중 데드레커닝의 일부 문제를 해결하고자 만든 간단한 프로젝트입니다.

*주의* <br>
길 찾기 중 벽 설치시 재탐색 기능은 아직 미구현입니다 <br>
벽을 먼저 설치한 이후 테스트 가능합니다. <br>

## 목적
### 데드레커닝 갑작스러운 방향 전환 문제 해결하기

언제나 클라이언트가 먼저 이동하고 서버는 늦게 전달을 받게 됩니다 <br>
일반적으로 비슷한 방향으로 이동할 경우에는 움직임이 자연스러웠습니다. <br>
하지만 90도 이상으로 방향을 변경한 경우 오차가 벌어지게 되는 문제가 있습니다. <br>

그래서 해당 문제를 90도 이상 방향을 변경한 경우 이를 감지하여 <br>
기존 0.25초마다 이동 동기화를 하는 것이 아닌 동적(0.1 -> 0.25)으로 처리하고자 하였습니다. <br>

## 테스트 환경
<img width="241" height="210" alt="image" src="https://github.com/user-attachments/assets/0c02feca-e52b-4057-b022-e92a11288d27" />

## 결과 요약
회복 패턴과 최소 주기 설정에 따라 결과는 다릅니다만, 현재 기준 일시적 누적 전송량 57% 증가 대비하여 <br>
평균 위치 오차를 27% 감소 및 낮은 오차 구간 발생 빈도가 62% 증가하여 안정적인 위치 동기화가 가능하였습니다. <br>

<img width="360" height="210" alt="image" src="https://github.com/user-attachments/assets/66ce613e-1096-4e42-aa53-7b48b6d3f896" />

<img width="360" height="210" alt="image" src="https://github.com/user-attachments/assets/e977bf1b-7d52-47b8-8dbd-64d53a05d448" />

## 결과 GIF

### 고정 주기
![고정 이동](https://github.com/user-attachments/assets/661e7ca4-309f-4c7c-ab18-2053ba76a9e1)

### 동적 주기
![동적 이동](https://github.com/user-attachments/assets/3c80a178-4236-4769-8e5f-e23cc36ec1ec)

## 주요 코드

### 방향 감지

경로 탐색을 시도했다면 이전 경로와 현재 경로를 비교하였는데 방향이 90도 이상 변경 되었을 경우 이를 감지하여 동기화 주기를 줄입니다. <br>

```
  // 경로 탐색
  std::list<Node*> path = mPathFinder->FindPath(mMap, Entity->mPosition, DestNode->mPosition);

  // 이전 탐색 경로가 있었다면
	if (!Entity->mPath.empty() && !path.empty())
	{
		Node* curNode = mMap->GetNodeFromPosition(Entity->mPosition);
		Node* oldNode = Entity->mPath.front();
		Node* nextNode = path.front();

		GridDirection currentDirection = Grid::GetGridDirection(curNode, oldNode);
		GridDirection nextDirection = Grid::GetGridDirection(curNode, nextNode);

    // 방향 감지
		if (Grid::IsAngleExceeded(currentDirection, nextDirection, 90))
		{
			// 즉시 동기화 주기를 낮춤
			Entity->mIntervalMoveSync = 0.1f;
		}
	}
```

```
// 방향을 가져와서 비교 후 Angle만큼 틀어져 있다면 감지합니다.
bool Grid::IsAngleExceeded(const GridDirection From, const GridDirection To, const int Angle)
{
	int fromAngle = GetGridDirectionAngle(From);
	int toAngle = GetGridDirectionAngle(To);

	int angleDiff = std::abs(fromAngle - toAngle);
	if (angleDiff > 180)
	{
		angleDiff = 360 - angleDiff;
	}

	return angleDiff >= Angle;
}
```

### 동기화 회복

동기화 회복의 경우에는 방향 감지 이후 줄어든 이동 동기화를 천천히 회복시키는 상황입니다.  <br>
그래서 0.1 -> 0.25까지 점전적으로 회복이 되어지도록 하였습니다.  <br>

```
// 최소값에서 최대값까지 0.015씩 증가하는 회복 코드입니다.
void Entity::RecoveyIntervalMoveSync()
{
	const float MinInterval = 0.1f;
	const float MaxInterval = 0.25f;
	const float TotalRange = MaxInterval - MinInterval;

	const float IncrementRatio = 0.1f;

	if (mIntervalMoveSync >= MaxInterval) return;

	float incrementStep = TotalRange * IncrementRatio;
	mIntervalMoveSync += incrementStep;

	if (mIntervalMoveSync > MaxInterval)
	{
		mIntervalMoveSync = MaxInterval;
	}
}
```

```
// 이동 동기화 주기를 고정 프레임에 의해 동작되면서 회복되어집니다.
entity->MoveTowardsNextPath(DeltaTime);

entity->mLastMoveSync += DeltaTime;
if (entity->mLastMoveSync > entity->mIntervalMoveSync)
{
	entity->RecoveyIntervalMoveSync();

  /* 이동 정보 전달 */
  
  entity->mLastMoveSync = 0.0f;
}
```

## Vcpkg
### SDL2 : 그래픽 및 입력
### Boost.asio : 네트워크

mkdir build <br>
cd build <br>

cmake .. -DCMAKE_TOOLCHAIN_FILE=C:/dev/vcpkg/scripts/buildsystems/vcpkg.cmake <br>
cmake --build . --config Release <br>

## 조작
좌 클릭 : 이동 <br>
우 클릭 : 벽 설치 <br>

## 사용법
귀찮으시겠지만 다음 줄을 찾아 주석처리 해주시면 됩니다... <br>
Entity->mIntervalMoveSync = 0.1f; <br>

## 참고
[이득우의 꼭 배워야하는 게임 알고리](https://www.inflearn.com/course/%EA%B2%8C%EC%9E%84-%EC%95%8C%EA%B3%A0%EB%A6%AC%EC%A6%98?srsltid=AfmBOop6dMp3k7lA91OPR5NQBIGTTnWZBma8r3uTrY9XFidST7RZB5sU) - A*를 구현하는데 참고 하였스니다.
