find_package("Vulkan" REQUIRED)

add_sample("hw_ray_tracer"
  SOURCES
    "hw_ray_tracer.cpp"
  PACKAGES
    boost_poly_collection
    boost_qvm
  LIBRARIES
    Boost::poly_collection
    Boost::qvm
)

target_link_libraries("hw_ray_tracer" PRIVATE "Vulkan::Vulkan")
