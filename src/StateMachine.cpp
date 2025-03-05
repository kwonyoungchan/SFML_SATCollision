#include "StateMachine.h"

void CStateMachine::AddState(StateRef newState, bool isReplacing)
{
	// newState가 유효한지 체크한다.
	if (newState == NULL) return;
	if (!this->_states.empty() && this->_states.top() == newState) return;
	// state를 buffer에 넣는다.
	if (isReplacing)
	{
		stateCalls.push(EState::REPLACE);
		stateBuffer.push(std::move(newState));
	}
	else
	{
		stateCalls.push(EState::ADD);
		stateBuffer.push(std::move(newState));
	}
}

void CStateMachine::RemoveState()
{
	stateCalls.push(EState::REMOVE);
}

void CStateMachine::ProcessStateChanges()
{ 
	// state call 확인 
	// state를 확인 
	// state에 맞는 로직 실행 
	if (stateCalls.empty()) return;
	currentStateCall = stateCalls.front();
	stateCalls.pop();
	switch (currentStateCall)
	{
		case EState::NONE:
		{
			// 아무것도 하지 않는다. 
			break;
		}
		case EState::ADD:
		{
			// 상태 체크
			if(!this->_states.empty())
			{
				_states.top()->Pause();
			}
			// 새로운 상태를 추가한다.
			this->_states.push(std::move(this->stateBuffer.front()));
			// 상태 초기화 시작
			this->_states.top()->Init();
			// 현재 상태를 NONE 으로 설정한다. 
			this->currentStateCall = EState::NONE;
			this->stateBuffer.pop();
			break;
		}
		case EState::REPLACE:
		{
			// 상태가 있는지 확인한다. 
			// 상태가 없으면 그냥 무시한다.
			if (this->_states.empty()) break;
			// 상태가 있으면 현재 상태와 새로운 상태를 교체한다. 
			this->_states.pop();
			this->_states.push(std::move(this->stateBuffer.front()));
			this->_states.top()->Init();
			// 현재 상태를 NONE 으로 설정한다. 
			this->currentStateCall = EState::NONE;
			this->stateBuffer.pop();
			break;
		}
		case EState::REMOVE:
		{
			// 상태가 있는지 확인한다. 
			// 상태가 없으면 그냥 무시한다. 
			if (this->_states.empty()) break;
			// 상태가 있으면 현재 상태를 삭제한다. 
			this->_states.pop();
			// 이전 상태가 있다면 이전 상태를 시작한다.
			this->_states.top()->Resume();
			this->currentStateCall = EState::NONE;
			break;
		}
	}
}

StateRef& CStateMachine::GetActiveState()
{
	return this->_states.top();
}

int CStateMachine::GetCurrentStateAmount()
{
	return this->_states.size();
}
