#ifndef RAII_H
#define RAII_H

#include <wx/filefn.h>
#include "Cpp11.h"

// helper for generic raii-like objects
#define AtExit(name,code) \
	struct name##_t { \
		bool _do; name##_t():_do(true) {} \
		void run_now() { code; _do = false; } \
		void cancel() { _do = false; } \
		~name##_t() { if (_do) run_now(); } \
	} name;


/**
* @brief RAII wrapper for objects allocated on heap (new), but with a life-cycle
* as if it where on the stack (attached to a local scope)
**/
template<class T>
class RaiiDeletePtr {
	T *&p;
public:
	RaiiDeletePtr(T *&ptr) : p(ptr) {}
	~RaiiDeletePtr() { delete p; }
};

// fms stands for faked-move-semantics, this project should still compile in pre c++11 compilers
template<class T> void fms_move(T *&des, T *&src) { des=src; src=nullptr; }
template<class T> T *fms_move(T *&src) { T *des=src; src=nullptr; return des; }
template<class T> T *&fms_delete(T *&des) { delete des; des=nullptr; return des; }

class BoolFlag;

/**
* RAII wrapper for handling flags, set a flag on creation and reset it on deletion
**/
template<typename T, typename U=bool, U SET_VALUE=true, U RESET_VALUE=false>
class FlagGuard {
	T *m_flag;
public:
	FlagGuard(T &f, bool force):m_flag(&f) { *m_flag=SET_VALUE; }
	FlagGuard(T *f):m_flag(f) { if (!m_flag || *m_flag==SET_VALUE) { m_flag=nullptr; } else *m_flag=SET_VALUE; }
	FlagGuard(T &f):m_flag(&f) { if (*m_flag==SET_VALUE) { m_flag=nullptr; } else *m_flag=SET_VALUE; }
	bool IsOk() { return m_flag!=nullptr; }
	void Release() { if (m_flag) *m_flag=RESET_VALUE; m_flag=nullptr; }
	~FlagGuard() { if (m_flag) *m_flag=RESET_VALUE; }
};

/**
* Class for bool flags (used mostly for masking events) that enforce use with FlagGuard, and ensure correct initialization
**/
class BoolFlag {
public:
	BoolFlag() : value(false) {}
	operator bool() { return value; }
private:
	template<typename T, typename U, U V1, U V2>
	friend class FlagGuard;
	BoolFlag &operator=(bool b) { value=b; return *this; }
	bool value;
};

typedef FlagGuard<BoolFlag,bool,true,false> BoolFlagGuard;
typedef FlagGuard<bool,bool,true,false> boolFlagGuard;


/**
* Wrapper class for ensuring class member variables initialization
**/
template<class T>
class NullInitializedPtr {
	T *ptr;
public:
	NullInitializedPtr() : ptr(nullptr) {}
	operator T*&() { return ptr; }
	operator const T*&() const { return ptr; }
	T *&operator=(T *other) { ptr=other; return ptr; }
};

template<class T>
class RaiiRestoreValue {
	T &variable;
	T original_value;
public:
	RaiiRestoreValue(T &var, T value) 
		: variable(var), original_value(var) 
		{ variable = value; }
	RaiiRestoreValue(T &var) 
		: variable(var), original_value(var) {}
	T GetOriginalValue() { return original_value; }
	~RaiiRestoreValue() { variable = original_value; }
};

class RaiiWorkDirChanger {
	wxString old_dir;
public:
	RaiiWorkDirChanger(const wxString &new_dir) 
		: old_dir(wxGetCwd()) { wxSetWorkingDirectory(new_dir); }
	void RestoreNow() { if (old_dir.Len()) wxSetWorkingDirectory(old_dir); old_dir=""; }
	~RaiiWorkDirChanger() { if (old_dir.Len()) wxSetWorkingDirectory(old_dir); }
};

#endif
