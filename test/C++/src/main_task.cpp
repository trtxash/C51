/**
 * @file	Basic C++ Program
 * @brief   C++ Primer Plus Ch.12~ch.13
 * @author 	TRTX-gamer
 * @version 0.0.1
 * @date 	2025-03-16 18:43
 */

#include <iostream>
#include <vector>

struct DataVectorStruct
{
    union DataUnion {
        bool b;
        char ch;
        int i;
        float f;
        double d;
    };

    std::vector<bool> vec_bool;
    std::vector<char> vec_char;
    std::vector<int> vec_int;
    std::vector<float> vec_float;
    std::vector<double> vec_double;
    std::vector<std::string> vec_string;
    std::vector<DataUnion> vec_union;
};

template <typename Type1, typename Type2, typename Type3> bool NumberInput(Type1 &value, Type2 min, Type3 max);

/**
 * @brief	对函数简要描述
 * @param 	参数说明，以’:’作为参数结束标志；
 * @arg
 * 参数里面可选择参量列举，对于可数情况可进行参量列举，同样以’:’作为参数结束标志；
 * @note  	注释，配合brief一起使用可以达到很好的注释效果；
 * @retval	返回值说明。
 */
int main()
{
    DataVectorStruct data_vec = {};

    data_vec.vec_int.reserve(10); // 预分配足够空间，避免频繁重新分配内存，确保引用不会因vector扩容失效。
    data_vec.vec_string.reserve(10);

    data_vec.vec_int.push_back(0);
    int &task_num = data_vec.vec_int.back(); // 重命名为任务变量，来自vector结构体的int临时变量

    while (1)
    {
        std::cout << "Enter task number: ";
        if (NumberInput(task_num, 1, 9))
        {
            switch (task_num) // switch语句里不能定义变量，因分支共用变量,故定义处加大括号，定义在块内
            {
            case 1: {
            }
            break;
            case 2: {
                // test git 2
            }
            break;
            case 3: {
            }
            break;
            case 4: {
            }
            break;
            case 5: {
            }
            break;
            case 6: {
            }
            break;
            case 7: {
            }
            break;
            case 8: {
            }
            break;
            case 9: {
            }
            break;
            default:
                std::cout << "no task : " << task_num << std::endl;
                break;
            }
        }
        else
        {
        }
    }

    data_vec.vec_int.pop_back();
    return 0;
}

/**
 * @brief	模板函数，读入输入的数据，并进行类型和范围检查，返回是否成功
 * @param 	value 	输入数据
 * @param 	min 	最小值
 * @param 	max 	最大值,都为0则不进行范围检查
 * @arg
 * @note
 * 只能处理整数、浮点数、布尔型数据类型，其他类型需要自行定义模板函数；
 * @retval	True    成功
 * @retval	False   失败
 */
template <typename Type1, typename Type2, typename Type3> bool NumberInput(Type1 &value, Type2 min, Type3 max)
{
    // 处理类型错误...
    if (!(std::cin >> value))
    {

        std::cout << "Invalid task number format. Please enter a valid task number." << std::endl;
        std::cin.clear();              // 必须先清除错误状态
        while (std::cin.get() != '\n') // 删除没有用的输入
            continue;                  // get rid of bad input
        return false;
    }
    // 不进行范围检查
    if (min == 0 && max == 0)
    {
    }
    else
    {
        if (value < min || value > max)
        {
            // 处理范围错误...
            std::cout << "Invalid task number range. Please enter a valid task number." << std::endl;
            std::cin.clear();              // 必须先清除错误状态
            while (std::cin.get() != '\n') // 删除没有用的输入
                continue;                  // get rid of bad input
            return false;
        }
    }
    // 删除没有用的输入
    while (std::cin.get() != '\n')
        continue; // get rid of bad input

    return true;
}