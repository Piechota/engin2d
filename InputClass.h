#ifndef _INPUT_CLASS_H_
#define _INPUT_CLASS_H_

class InputClass{  
private:
	bool m_keys[256];
public:
	InputClass();
	InputClass(const InputClass&);
	~InputClass();

	void Initialize();

	bool IsKeyDown(unsigned int);

	void KeyDown(unsigned int);
	void KeyUp(unsigned int);
};

#endif