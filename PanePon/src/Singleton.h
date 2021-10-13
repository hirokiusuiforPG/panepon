#pragma once

template <typename _T>
class CSingleton {
protected:
	CSingleton() {
	}

	virtual ~CSingleton() {
//		m_pInst = nullptr;
	}

//	static _T* m_pInst;

public:
	static _T* Inst() {
		static _T inst;
		return &inst;
//		if ( m_pInst == nullptr ){
//			m_pInst = new _T;
//		}
//		return m_pInst;
	};
};

//template<typename _T>
//_T* CSingleton<_T>::m_pInst = nullptr;