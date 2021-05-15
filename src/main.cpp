#include "../vendor/spriter/spriter.h"
#include "../vendor/spriter/utils/logger.h"

int main(){
    if(!spriter::init()){
        ERR("Failed to initialize spriter!");
        return -1;
    }
}
