#ifndef _TEXT_INC
#define _TEXT_INC

class text
{
    char *data;
    unsigned int sl;
    unsigned int size;
public:
	text();
	text(const char*);
	virtual ~text();

    void create(char *);
    char *getword();
	char *getcommaword();
    int getint();
    double getfloat();

    int countword(char *);
	int countwordfromhere(char *);
    int countchar(char);
    void reset();
    void destroy();
    void goback();
	bool seek(char *);
    int eof();
	unsigned int getPos();
	BOOL setPos(unsigned int posicion);
};

#endif
