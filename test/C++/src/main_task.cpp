/**
 * @file	Basic C++ Program
 * @brief   C++ Primer Plus Ch.12~ch.13
 * @author 	TRTX-gamer
 * @version 0.0.1
 * @date 	2025-03-16 18:43
 */

#include <bitset>
#include <iostream>
#include <string>

template <typename Type1, typename Type2, typename Type3>
bool NumberInput(Type1 &value, Type2 min, Type3 max);

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
    int task_num;

    while (1)
    {
        std::cout << "Enter task number: ";
        if (NumberInput(task_num, 1, 9))
        {
            switch (task_num)
            {
            case 1:
            {
                // 测试原码反码补码的转换，以及加减乘除计算
                int ture_num;
                std::cout << "Enter a number: ";
                if (NumberInput(ture_num, INT_MIN, INT_MAX))
                {
                    std::string ori_str, rev_str, comp_str;
                    // int ori_num, rev_num, comp_num;
                    std::cout << "\nTrue number: " << ture_num << std::endl;
                    // 原码转换
                    if (ture_num >= 0)
                    {
                        ori_str = std::bitset<32>(ture_num).to_string();
                        rev_str = ori_str;
                        comp_str = ori_str;
                    }
                    else
                    {
                        std::cout << "direct output: " << std::endl;
                        ori_str = std::bitset<32>(ture_num).to_string();       // 得到的是ture_num的补码，因为计算机中实际存储的是补码形式
                        rev_str = std::bitset<32>(~ture_num).to_string();      //
                        comp_str = std::bitset<32>(~ture_num + 1).to_string(); // 一个负数的补数=模-该数
                        std::cout << "Original code: " << ori_str << std::endl;
                        std::cout << "Reverse code: " << rev_str << std::endl;
                        std::cout << "Complement code: " << comp_str << "\n"
                                  << std::endl;

                        std::cout << "because of the direct output, the original code is the complement code" << std::endl;
                    }
                }
            }
            break;
            case 2:
            {
            }
            break;
            case 3:
            {
            }
            break;
            case 4:
            {
            }
            break;
            case 5:
            {
            }
            break;
            case 6:
            {
            }
            break;
            case 7:
            {
            }
            break;
            case 8:
            {
            }
            break;
            case 9:
            {
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

    return 0;
}

/**
 * @brief	模板函数，读入输入的数据，并进行类型和范围检查，返回是否成功
 * @param 	value 	输入数据
 * @param 	min 	最小值
 * @param 	max 	最大值,都为0则不进行范围检查
 * @arg 只能处理整数、浮点数、布尔型数据类型，其他类型需要自行定义模板函数；
 * @note
 * @retval	True    成功
 * @retval	False   失败
 */
template <typename Type1, typename Type2, typename Type3>
bool NumberInput(Type1 &value, Type2 min, Type3 max)
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