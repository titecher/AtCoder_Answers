#ifndef ORDER_HPP
#define ORDER_HPP

#include <cassert>

class order {
public:
  using order_num_type = int_fast64_t;
private:
  static const order_num_type na;
  order_num_type id, dst, start_time, end_time;
  
public:
  order();
  order(order_num_type id_, order_num_type dst_,
	order_num_type start_time_, order_num_type end_time_);
  order(order_num_type id_, order_num_type dst_,
	order_num_type start_time_);

  bool complete_order();

  order_num_type duration();

  void register_end_time(order_num_type t);

  std::tuple<order_num_type, order_num_type, order_num_type, order_num_type> get_order_info() const;
};

using o_nt = order::order_num_type;
const o_nt order::na = -1;

order::order() = default;
order::order(o_nt id_, o_nt dst_,
	     o_nt start_time_, o_nt end_time_) :
  id(id_), dst(dst_), start_time(start_time_), end_time(end_time_) {}
order::order(o_nt id_, o_nt dst_,
	     o_nt start_time_) :
  id(id_), dst(dst_), start_time(start_time_), end_time(na) {}

bool order::complete_order() {
  return end_time != na;
}

o_nt order::duration() {
  if(!complete_order()) return -1;
  return end_time - start_time;
}

void order::register_end_time(o_nt t) {
  assert(end_time == na);
  end_time = t;
}

std::tuple<o_nt, o_nt, o_nt, o_nt> order::get_order_info() const {
  return std::make_tuple(id, dst, start_time, end_time);
}

#endif
