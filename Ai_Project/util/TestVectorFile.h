#pragma once
#include "CVector2D.h"


static void
printOptions()
{
  std::cout << R"..(input which operation you what
0) exit
1) add vectors
2) subtract vectors
3) multiple vectors
4) dot product of dot(vector1 , vector2)
5) get the smallest value
6) get the biggest value
7) get the distance between the vectors
8) get the distance between the vectors Squared
9) get the projection of vector2 on vector1
10) get the ceiling value of vector1
11) get the floor value of vector1
12) get the rounding  value of vector1
13) apply the ceiling operation on vector1 
14) apply the floor operation on vector1
15) apply the rounding operation on vector1
16) rotate vector1 x degrees
17) rotate vector1 x radians
18) print the 2 vectors
19) give vectors new values
>>>)..";
}

static void
changeVectorValues(enVector2& userVector, enVector2& otherVector)
{
  std::cout << "give x and y values to Vector1\n X =";
  std::cin >> userVector.X;
  std::cout << "\n Y =";
  std::cin >> userVector.Y;

  std::cout << "\n give x and y values to Vector2 \n X=";
  std::cin >> otherVector.X;
  std::cout << "\n Y =";
  std::cin >> otherVector.Y;

  std::cout << "\n\nresult vector 1 = " << userVector << "\n vector 2 =" << otherVector << '\n' << std::endl;
}

static void
testVectorMath(enVector2& userVector, enVector2& otherVector)
{
  uint32_t options(1u);
  while (options != 0u)
  {
    printOptions();
    std::cin >> options;
    switch (options)
    {
    case(1):
      std::cout << "\n=============\n[" << enVector2(userVector + otherVector) << "]\n=============\n";
      break;

    case(2):
      std::cout << "\n=============\n[" << enVector2(userVector - otherVector) << "]\n=============\n";
      break;

    case(3):
      std::cout << "\n=============\n[" << enVector2(userVector % otherVector) << "]\n=============\n";
      break;
    case(4):
      std::cout << "\n=============\n[" << userVector.DotProduct(otherVector) << "]\n=============\n";
      break;
    case(5):
      std::cout << "\n=============\n[" << userVector.Min() << "]\n=============\n";
      break;
    case(6):
      std::cout << "\n=============\n[" << userVector.Max() << "]\n=============\n";
      break;
    case(7):
      std::cout << "\n=============\n[" << userVector.Distance(otherVector) << "]\n=============\n";
      break;
    case(8):
      std::cout << "\n=============\n[" << userVector.DistanceSquared(otherVector) << "]\n=============\n";
      break;
    case(9):
      std::cout << "\n=============\n[" << userVector.Projection(otherVector) << "]\n=============\n";
      break;
    case(10):
      std::cout << "\n=============\n[" << userVector.CeilReturn() << "]\n=============\n";
      break;
    case(11):
      std::cout << "\n=============\n[" << userVector.FloorReturn() << "]\n=============\n";
      break;
    case(12):
      std::cout << "\n=============\n[" << userVector.RoundReturn() << "]\n=============\n";
      break;
    case(13):
      userVector.CeilSelf();
      std::cout << "\n=============\n[" << userVector << "]\n=============\n";
      break;
    case(14):
      userVector.FloorSelf();
      std::cout << "\n=============\n[" << userVector << "]\n=============\n";
      break;
    case(15):
      userVector.RoundSelf();
      std::cout << "\n=============\n[" << userVector << "]\n=============\n";
      break;

    case(16):
    {
      float userDegrees{ 0.0f };
      std::cout << "\n insert the amount of degrees you what for the vector =";
      std::cin >> userDegrees;
      std::cout << "\n=============\n[" << userVector.RotateReturnDeg(userDegrees) << "]\n=============\n";
    }
    break;

    case(17):
    {
      float userRadians{ 0.0f };
      std::cout << "\n insert the amount of radians you what for the vector =";
      std::cin >> userRadians;
      std::cout << "\n=============\n[" << userVector.RotateReturnRad(userRadians) << "]\n=============\n";
    }
    break;

    case(18):
      std::cout << "\nvector1 = " << userVector << '\n'
        << "vector2 = " << otherVector << std::endl;
      break;
    case(19):
      changeVectorValues(userVector, otherVector);
      break;
    case(0):
    default:
      break;
    }


  }

}

