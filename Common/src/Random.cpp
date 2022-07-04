#include <Random.h>

int Random::Randomize(int min, int max)
{
	int result = min + rand() % (max - min + 1);

	return result;
}
