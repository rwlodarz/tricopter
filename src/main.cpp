/*
 * main.cpp
 *
 *  Created on: Jul 3, 2015
 *      Author: rwlodarz
 */

#include "lib/include/logger.hpp"


int main()
{
    for(int i = 0; i < 100000; ++i)
        LOG(ERROR, "dupa");

    return 0;
}
