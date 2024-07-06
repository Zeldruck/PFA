#include "my_lib/Bonus/Loading.h"

#define STRING_SIZE_MAX 100 

void Loading::Print(InfluenceEnum influence , std::string step)
{

    step.size();

    int size        = STRING_SIZE_MAX - step.size()-1;
    int secondSize  = size/2;
    int firstSize   = size - secondSize;

    std::string firstStr;
    std::string secondStr;

    switch (influence)
    {
        case Huge:

            if (step.size()-1 >= STRING_SIZE_MAX)
            {
                Log::PrintError(Low, "Loading::print() ", "The message is too large for the function try with lenght under 100 character");break;
            }

            firstStr.push_back('|');
            firstStr.push_back('|');
            firstStr.push_back(' ');

            for (int i = 0; i < size; i++)
            {
                if (i < firstSize)
                    firstStr.push_back('X');
                else
                    secondStr.push_back('X');
            }

            secondStr.push_back(' ');
            secondStr.push_back('|');
            secondStr.push_back('|');
            
            std::cout << " " << green_ << firstStr << step << secondStr << reset_ << std::endl;break;

        case Large:
                
            if (step.size()-1 >= STRING_SIZE_MAX)
            {
                Log::PrintError(Low, "Loading::print() ", "The message is too large for the function try with lenght under 100 character");break;
            }

            for (int i = 0; i < size; i++)
            {
                if (i < firstSize)
                    firstStr.push_back('=');
                else
                    secondStr.push_back('=');
            }
            
            std::cout << " " << green_ << "|| " << cyan_ << firstStr << step << secondStr << green_ << " ||" << reset_ << std::endl;break;

        case Small:

            if (step.size()-1 >= STRING_SIZE_MAX)
            {
                Log::PrintError(Low, "Loading::print() ", "The message is too large for the function try with lenght under 100 character");break;
            }

            for (int i = 0; i < size; i++)
            {
                step.push_back(' ');
            }
            
            std::cout << " " << green_ << "|| " << magenta_ << step << green_ << " ||" << reset_ << std::endl;break;
    }
}