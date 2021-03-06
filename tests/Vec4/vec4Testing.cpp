#include <gtest/gtest.h>
#include <ngl/Types.h>
#include <ngl/Vec4.h>
#include <ngl/Mat4.h>
#include <string>
#include <sstream>


int main(int argc, char **argv)
{
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

std::string print(const ngl::Vec4 &_m)
{
  std::stringstream ret;
  ret<<'(';
  for(size_t i=0; i<4; ++i)
    ret<<_m.m_openGL[i]<<',';
  ret<<"\b)\n";
  return ret.str();
}



TEST(NGLVec4,DefaultCtor)
{
  ngl::Vec4 test;
  ngl::Vec4 result(0.0f,0.0f,0.0f,1.0);
  EXPECT_TRUE(test == result);
}

TEST(NGLVec4,SubScript)
{
  ngl::Vec4 test(1.0f,2.0f,3.0f,4.0f);

  EXPECT_FLOAT_EQ(test[0], 1.0f);
  EXPECT_FLOAT_EQ(test[1],2.0f);
  EXPECT_FLOAT_EQ(test[2], 3.0f);
  EXPECT_FLOAT_EQ(test[3], 4.0f);

}



TEST(NGLVec4,FloatCtor)
{
  ngl::Vec4 test(1.0f,2.0f,3.0f,4.0f);
  ngl::Vec4 result(1.0f,2.0f,3.0f,4.0f);

  EXPECT_TRUE(test == result);
}


TEST(NGLVec4,CopyCtor)
{
  ngl::Vec4 test(1.0f,2.0f,3.0f,5.0f);
  ngl::Vec4 copy(test);
  ngl::Vec4 result(1.0f,2.0f,3.0f,5.0f);
  EXPECT_TRUE(copy == result);
}

TEST(NGLVec4,AssignOperator)
{
  ngl::Vec4 test(1.0f,2.0f,3.0f);
  ngl::Vec4 copy=test;
  ngl::Vec4 result(1.0f,2.0f,3.0f);
  EXPECT_TRUE(copy == result);
}


TEST(NGLVec4,VectorTest)
{
  std::vector<ngl::Vec4> a(10);
  std::vector<ngl::Vec4> b(10);
  float i=0.0f;
  for(auto &v : a)
  {
    v.set(i,i+1,i+2);
  ++i;
  }
  for(size_t i=0; i<a.size(); ++i)
  {
    b[i]=a[i];
  }
  for(size_t i=0; i<a.size(); ++i)
  {
    EXPECT_FLOAT_EQ(a[i][0], b[i][0]);
    EXPECT_FLOAT_EQ(a[i][1],b[i][1]);
    EXPECT_FLOAT_EQ(a[i][2], b[i][2]);
    EXPECT_FLOAT_EQ(a[i][3], b[i][3]);
    ASSERT_TRUE(a[i]==b[i]);
  }

}

TEST(NGLVec4,DotProduct)
{
  ngl::Vec4 a(1.0f,2.0f,3.0f);
  ngl::Vec4 b(4.0f,5.0f,6.0f);
  ASSERT_FLOAT_EQ(a.dot(b),32.0f);
}

TEST(NGLVec4,NULL)
{
  ngl::Vec4 test(1,2,4);
  test.null();
  ASSERT_TRUE(test==ngl::Vec4::zero());
}

TEST(NGLVec4,normalize)
{
  ngl::Vec4 test(22.3f,0.5f,10.0f);
  test.normalize();
  ngl::Vec4 result(0.912266f,0.0204544f,0.409088f);
  ASSERT_TRUE(test==result);

}


TEST(NGLVec4,Inner)
{
  ngl::Vec4 a(1.0,2.0,3.0);
  ngl::Vec4 b(3.0,4.0,5.0);
  ASSERT_FLOAT_EQ(a.inner(b),26.0f);
}

TEST(NGLVec4,Outer)
{
  ngl::Vec4 a(1.0f,2.0f,3.0f,4.0f);
  ngl::Vec4 b(5.0f,6.0f,7.0f,8.0f);
  ngl::Mat4 outer=a.outer(b);
  ngl::Mat4 result(5,6,7,8,10,12,14,16,15,18,21,24,20,24,28,32);
  ASSERT_TRUE(outer==result);
}

TEST(NGLVec4,Length)
{
  ngl::Vec4 a(22,1,32);

  ASSERT_NEAR(a.length(),38.845f,0.001f);
}

TEST(NGLVec4,LengthSquared)
{
  ngl::Vec4 a(22,1,32);

  ASSERT_NEAR(a.lengthSquared(),1509.0f,0.001f);
}

TEST(NGLVec4,Cross2)
{
  ngl::Vec4 a=ngl::Vec4::up();
  ngl::Vec4 b=ngl::Vec4::left();
  ngl::Vec4 c;
  c.cross(a,b);
  ASSERT_TRUE(c==ngl::Vec4::in());
}

TEST(NGLVec4,Cross1)
{
  ngl::Vec4 a=ngl::Vec4::up();
  ngl::Vec4 b=ngl::Vec4::left();
  ngl::Vec4 c=a.cross(b);
  ASSERT_TRUE(c==ngl::Vec4::in());
}









