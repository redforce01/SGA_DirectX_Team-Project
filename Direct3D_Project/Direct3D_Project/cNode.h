#pragma once
#include "cTransform.h"

class cTransform;
class cBoundSphere;

class cNode
{

private:
	D3DXVECTOR3 m_PosVec;
	cBoundSphere* m_NodeSpere;
	cTransform m_posTrans;
	vector<int> m_vIdx;
	vector<cNode*>	m_vEdgeNode;
	vector<cNode*>::iterator	m_viEdgeNode;
	int m_ID;
	int m_EdgeNum;
	bool m_isVisit;
	bool m_isCheck;

public :
	cNode();
	void SetNextRotate(D3DXVECTOR3 vec)
	{
		m_posTrans.LookPosition(vec * - 1, D3DXVECTOR3(0,1,0));
	}
	void Init(D3DXVECTOR3 vec);
	cTransform getTrans() { return m_posTrans; }
	D3DXVECTOR3 getVecPos() { return m_PosVec;  }
	void pushEdgeNode(cNode* node);
	float CalEdge(int ToNum);

	int getID() { return m_ID; }
	bool getisVisited() { return m_isVisit; }
	bool getisChecked() { return m_isCheck; }
	int getEdgeNum() { return m_EdgeNum;  }

	void setVisit(bool tf) { m_isVisit = tf; }
	void setID(int id) { m_ID = id;  }
	void setEdgeNum(int num) { m_EdgeNum = num; }

	void Render();
	void PushIdx(int idx) { m_vIdx.push_back(idx); }

	int getEdgeIdx(int i) { return m_vIdx[i]; }



};

