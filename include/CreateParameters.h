#include "Usings.h"
#include "Strategy.h"

class CreateParameters
{
    public:
        CreateParameters() = default;


        ParameterList CreateDoubleMAParameterList()
        {
            for(int i = 0; i < 200; i++)
            {
                for(int j = i; j < 200; j++)
                {
                    if(i < j)
                    {
                        paramlist_.push_back(ParameterInstance(i, j));
                    }
                };
            }
            int size = paramlist_.size();
            printf("Created %d parameter instances.\n", size);
            return paramlist_;
        };

        ParameterList CreateMAParameterList()
        {
            for(int i = 0; i < 200; i++)
            {
                paramlist_.push_back(ParameterInstance(i));
            }
            int size = paramlist_.size();
            printf("Created %d parameter instances.\n", size);
            return paramlist_;
        };
        
    private:
        ParameterList paramlist_;

};