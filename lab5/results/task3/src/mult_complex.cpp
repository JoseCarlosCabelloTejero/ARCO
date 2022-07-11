#include <CL/sycl.hpp>
#include <iomanip>
#include <vector>
#include "dpc_common.hpp"
#include "Complex.hpp"

using namespace sycl;
using namespace std;

// Number of complex numbers passing to the DPC++ code
static const int num_elements = 10000;

// in_vect1 and in_vect2 are the vectors with num_elements complex nubers and
// are inputs to the parallel function
void DpcppParallel(queue &q, std::vector<Complex2> &in_vect1,
                   std::vector<Complex2> &in_vect2,
                   std::vector<Complex2> &out_vect)
{

  auto R = range(in_vect1.size());

  buffer bufin_vect1(in_vect1);
  buffer bufin_vect2(in_vect2);

  buffer bufout_vect(out_vect);

  std::cout << "Target Device: " << std::endl;
  std::cout << "Device name: " << q.get_device().get_info<info::device::name>() << std::endl;
  std::cout << "Vendor: " << q.get_device().get_info<info::device::vendor>()<< std::endl;
  std::cout << "Version: " << q.get_device().get_info<info::device::version>()<< std::endl;
  // TODO: Get info from the device print here

  q.submit([&](auto &h)
           {
             // Accessors set as read mode
             // How we should access bufin_vect1 and 2: read_only, write_only, read_write...
             accessor V1(bufin_vect1, h, read_only); //TODO: Add here your decision);
             accessor V2(bufin_vect2, h, read_only); //TODO: Add here your decision);

             // How we should access bufout_vect: read_only, write_only, read_write...
             accessor V3(bufout_vect, h, write_only);//TODO: Add here your decision);
             h.parallel_for(R, [=](auto i)
                            {
                              V3[i] = V1[i].complex_mul(V2[i]);
                            });
           });
  q.wait();
  // TODO add code to wait the work
}

void DpcppScalar(std::vector<Complex2> &in_vect1,
                 std::vector<Complex2> &in_vect2,
                 std::vector<Complex2> &out_vect)
{
  for (int i = 0; i < in_vect1.size(); i++)
  {
    out_vect[i] = in_vect1[i].complex_mul(in_vect2[i]);
  }
}

// Compare the results of the two output vectors from parallel and scalar. They
// should be equal
int Compare(std::vector<Complex2> &v1, std::vector<Complex2> &v2)
{
  int ret_code = 1;
  if (v1.size() != v2.size())
  {
    ret_code = -1;
  }
  for (int i = 0; i < v1.size(); i++)
  {
    if (v1[i] != v2[i])
    {
      ret_code = -1;
      break;
    }
  }
  return ret_code;
}
int main()
{
  // Declare your Input and Output vectors of the Complex2 class
  vector<Complex2> input_vect1;
  vector<Complex2> input_vect2;
  vector<Complex2> out_vect_parallel;
  vector<Complex2> out_vect_scalar;

  for (int i = 0; i < num_elements; i++)
  {
    input_vect1.push_back(Complex2(i + 2, i + 4));
    input_vect2.push_back(Complex2(i + 4, i + 6));
    out_vect_parallel.push_back(Complex2(0, 0));
    out_vect_scalar.push_back(Complex2(0, 0));
  }

  // Initialize your Input and Output Vectors. Inputs are initialized as below.
  // Outputs are initialized with 0
  cpu_selector selector;
  queue q(selector, dpc_common::exception_handler);
  // Call the DpcppParallel with the required inputs and outputs
  DpcppParallel(q, input_vect1, input_vect2, out_vect_parallel);

  std::cout << "****************************************Multiplying Complex numbers "
               "in Parallel********************************************************"
            << std::endl;

  // Print the outputs of the Parallel function
  int indices[]{0, 1, 2, 3, 4, (num_elements - 1)};
  constexpr size_t indices_size = sizeof(indices) / sizeof(int);

  for (int i = 0; i < indices_size; i++)
  {
    int j = indices[i];
    if (i == indices_size - 1)
      std::cout << "...\n";
    std::cout << "[" << j << "] " << input_vect1[j] << " * " << input_vect2[j]
              << " = " << out_vect_parallel[j] << "\n";
  }
  // Call the DpcppScalar function with the required input and outputs
  DpcppScalar(input_vect1, input_vect2, out_vect_scalar);

  // Compare the outputs from the parallel and the scalar functions. They should
  // be equal

  int ret_code = Compare(out_vect_parallel, out_vect_scalar);
  if (ret_code == 1)
  {
    std::cout << "Complex multiplication successfully run on the device"
              << "\n";
  }
  else
    std::cout
        << "*********************************************Verification Failed. Results are "
           "not matched**************************"
        << "\n";

  return 0;
}
