#ifndef _ACTIVE_TIME_H_
#define _ACTIVE_TIME_H_

    class Active_Time {
    private:
        unsigned short int arrival;
	unsigned short int dispetch;

    public:
        Active_Time(unsigned short int, unsigned short int);
	~Active_Time(void);

	unsigned short int get_Begin();
	unsigned short int get_End();
    };

#endif /* _ACTIVE_TIME_H_ */
