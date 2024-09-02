
#include <stdbool.h>
#include <stdlib.h>

typedef struct _mutex_lock {
    volatile bool locked;
}mutex_lock;

mutex_lock* InitMutexLock();
bool AcquireMutexLockWithLoop (mutex_lock* lock);
bool ReleaseMutexLock(mutex_lock* lock);
void DestroyLock(mutex_lock* lock);