#ifndef STAN_IO_WRITE_MODEL_HPP
#define STAN_IO_WRITE_MODEL_HPP

#include <stan/interface_callbacks/writer/base_writer.hpp>
#include <string>

namespace stan {
  namespace io {

    void write_model(interface_callbacks::writer::base_writer& writer,
                     const std::string model_name) {
      writer("model = " + model_name);
    }

  }
}
#endif
