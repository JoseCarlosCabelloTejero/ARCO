#include <CL/sycl.hpp>
using namespace sycl;

static const int N = 256;

int main() {
  queue q;
  std::cout << "Device : " << q.get_device().get_info<info::device::name>()
            << std::endl;

  // USM allocation and initialization
  // Here malloc_shared creates a view for the programmer that abstracts the memory implementation of each device
  int *data = malloc_shared<int>(N, q);

  // Init
  for (int i = 0; i < N; i++) data[i] = 10;

  // We want to print 20 as the result
  // But we don't have any implicit data dependence
  // So each task can run in parallel and, therefore, could lead to errors
  q.parallel_for(range<1>(N), [=](id<1> i) { data[i] += 2; });

  q.parallel_for(range<1>(N), [=](id<1> i) { data[i] += 3; });

  q.parallel_for(range<1>(N), [=](id<1> i) { data[i] += 5; }).wait();

  for (int i = 0; i < N; i++) std::cout << data[i] << " ";
  std::cout << std::endl;
  free(data, q);
  return 0;
}
