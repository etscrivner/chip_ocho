#ifndef CPU_H_YGSGC2C5
#define CPU_H_YGSGC2C5

class cpu_t
{
public:
	cpu_t ();
	virtual ~cpu_t ();
private:
	unsigned int pc; // The address of the next instruction to execute
};

#endif /* end of include guard: CPU_H_YGSGC2C5 */
