#include "StdAfx.h"
#include "cMainGame.h"
#include "cImage.h"

#include "cScene_Main.h"
#include "cScene_Game.h"
#include "cScene_Test.h"

cMainGame::cMainGame( void )
{
}

cMainGame::~cMainGame( void )
{
}

//셋팅
HRESULT cMainGame::Init( void )
{
	//디바이스 생성
	CreateDevice();

	//매니져 셋팅
	TIME_MGR->Init();
	LOG_MGR->Init( LOG_WINDOW | LOG_FILE, g_hWnd, "Dump" );
	DXFONT_MGR->Init(Device);
	GIZMO_MGR->Init(Device);
	SPRITE_MGR->Init(Device);
	SCENE_MGR->Init();

	SOUNDMANAGER->init();
	SOUNDDATA->Init();
	EVENT_MGR->Init();

	SCENE_MGR->AddScene("main", new cScene_Main);
	SCENE_MGR->AddScene("game", new cScene_Game);
	SCENE_MGR->AddScene("test", new cScene_Test);
	//SCENE_MGR->AddLoadingScene("loading", new cScene_Loading);

	SCENE_MGR->ChangeScene("game");

	return S_OK;
}

//해제
void cMainGame::Release()
{
	//매니져 해제
	TIME_MGR->Release();
	cTimeMgr::ReleaseInstance();
	KEY_MGR->Release();
	cKeyMgr::ReleaseInstance();
	LOG_MGR->Release();
	cLogMgr::ReleaseInstance();
	GIZMO_MGR->Release();
	cGizmoManager::ReleaseInstance();
	SCENE_MGR->Release();
	cScene_Mgr::ReleaseInstance();

	cPhysicManager::ReleaseInstance();

	RESOURCE_TEXTURE->ClearResource();
	cResourceMgr_Texture::ReleaseInstance();
	RESOURCE_TEXTURE->ClearResource();
	cResourceMgr_Texture::ReleaseInstance();
	RESOURCE_FX->ClearResource();
	cResourceMgr_ShaderFX::ReleaseInstance();
	RESOURCE_STATICXMESH->ClearResource();
	cResourceMgr_XStaticMesh::ReleaseInstance();

	EVENT_MGR->Release();
	cEventObjectManager::ReleaseInstance();
	SOUNDMANAGER->release();
	cSoundManager::ReleaseInstance();
	SOUNDDATA->Release();
	cSoundData::ReleaseInstance();


	//디바이스 해제
	ReleaseDevice();
}

//업데이트
void cMainGame::Update()
{
	//타임매니져 업데이트
	TIME_MGR->UpdateTime(60.0f);

	//한프레임 갱신 시간
	double timeDelta = TIME_MGR->GetFrameDeltaSec();

	//씬업데이트
	SCENE_MGR->Update(timeDelta);
}

//드로우
void cMainGame::Draw()
{
	//버퍼를 청소한다
	HRESULT result = Device->Clear(
		0,							//청소할 영역의 D3DRECT 배열 갯수		( 전체 클리어 0 )
		NULL,						//청소할 영역의 D3DRECT 배열 포인터		( 전체 클리어 NULL )
		D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL,		//청소될 버퍼 플레그 ( D3DCLEAR_TARGET 컬러버퍼, D3DCLEAR_ZBUFFER 깊이버퍼, D3DCLEAR_STENCIL 스텐실버퍼
		0xff123434,					//컬러버퍼를 청소하고 채워질 색상( 0xAARRGGBB )
		1.0f,						//깊이버퍼를 청소할값 ( 0 ~ 1, 0 이 카메라에서 제일가까운 1 이 카메라에서 제일 먼 )
		0							//스텐실 버퍼를 채울값
		);

	//버퍼 청소가 성공했다면.......
	if (SUCCEEDED(result))
	{
		//디바이스 랜더링 시작 명령
		Device->BeginScene();

		//랜더링 명령

		//씬랜더
		SCENE_MGR->Render();

#ifdef _DEBUG	//디버그 모드에서만 실행
		//디바이스 랜더링 종료 명령
		//월드 그리드
		//GIZMO_MGR->WorldGrid(1, 10);

		//타임정보 출력
		TIME_MGR->DrawTimeInfo();
#endif

		//디바이스 랜더링 종료 명령
		Device->EndScene();

		//디바이스 로스트를 검사한다
		HandleLostGraphicsDevice();

		//랜더링된 버퍼내용을 화면에 전송
		Device->Present(0, 0, 0, 0);
	}

}

//////////////////////////////////////////////////////////////////////////

//메인 프로시져 함수
LRESULT cMainGame::MainProc( HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam )
{
	switch ( iMessage )
	{
	case WM_KEYDOWN:
		switch ( wParam )
		{
		case VK_ESCAPE:
			DestroyWindow( hWnd );
			break;
		}
		break;

	case WM_DESTROY:			//윈도우가 파괴된다면..
		PostQuitMessage( 0 );	//프로그램 종료 요청 ( 메시지 루프를 빠져나가게 된다 )
		break;
	}
	return DefWindowProc( hWnd, iMessage, wParam, lParam );
}

