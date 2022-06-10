
#include "date.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <cstdint>
#include <ratio>
#include <limits>
#include <type_traits>
#include <cmath>


namespace impl {
struct clock_t {
	using period = std::ratio<1>;
	using rep = double;
    using duration = std::chrono::duration<rep,period>;
	using time_point = std::chrono::time_point<clock_t>;
    static constexpr bool is_steady = false;

	static constexpr char NA[] = "N/A";
	static constexpr date::sys_days epoch = date::year{1970}/date::month{1}/date::day{};

	template <typename Rep> static std::chrono::time_point<clock_t,duration> nan(){
		namespace ch = std::chrono;
		return ch::time_point<clock_t>( duration( std::numeric_limits<Rep>::quiet_NaN() ) );
	}

	template<typename Duration> static std::chrono::time_point<std::chrono::system_clock, Duration>
    to_sys(const std::chrono::time_point<clock_t, clock_t::duration>& from){
		using Rep = typename Duration::rep;
		using ratio_e =  std::ratio_divide<date::sys_days::period,period>;
		using ratio_s =  std::ratio_divide<period, typename Duration::period>;

		constexpr rep e =  ratio_e::num / static_cast<rep>( ratio_e::den );
		constexpr Rep s =  ratio_s::num / ratio_s::den;
		Rep ticks = static_cast<Rep>( s*from.time_since_epoch().count() +  e * s * epoch.time_since_epoch().count() );
		return date::sys_time<Duration>{ Duration( ticks ) };
    }

	template<typename Duration> static std::chrono::time_point<clock_t, clock_t::duration>
    from_sys(const date::sys_time<Duration>& from){
		using Rep = rep;
		using ratio_e =  std::ratio_divide<date::sys_days::period,period>;
		using ratio_s =  std::ratio_divide<typename Duration::period,period>;

		constexpr Rep e =  ratio_e::num / static_cast<Rep>( ratio_e::den );
		constexpr Rep s =  ratio_s::num / static_cast<Rep>( ratio_s::den );

		return time_point{
			duration( s * from.time_since_epoch().count() - e * epoch.time_since_epoch().count()  ) };
    }
	
	static time_point now() noexcept {
		using Duration = std::chrono::system_clock::duration;
        return from_sys<Duration>(
				std::chrono::system_clock::now() );
    }
};

constexpr date::sys_days clock_t::epoch;
constexpr char clock_t::NA[];
}


template <class CharT, class Traits, class Duration> std::basic_ostream<CharT, Traits>& to_stream(
		std::basic_ostream<CharT, Traits>& os, const CharT* fmt, const std::chrono::time_point<impl::clock_t,Duration>& tp){
	using namespace date;
	using namespace std;
	using Rep = typename Duration::rep;

	if( !std::isnan(tp.time_since_epoch().count()) )
		return date::to_stream(os, fmt, impl::clock_t::to_sys<std::chrono::duration<long,typename Duration::period>>(tp) );
	os << impl::clock_t::NA;
	return os;
}
template <class CharT, class Traits, class Duration> std::basic_ostream<CharT, Traits>&
		operator<<(std::basic_ostream<CharT, Traits>& os, const std::chrono::time_point<impl::clock_t,Duration>& tp) {

	const CharT fmt[] = {'%', 'F', 'T', '%', 'T', 'Z', CharT{}};
    return to_stream(os, fmt,tp);
}

template <class Duration, class CharT, class Traits, class Alloc = std::allocator<CharT>> std::basic_istream<CharT, Traits>& 
	from_stream(std::basic_istream<CharT, Traits>& is, const CharT* fmt, std::chrono::time_point<impl::clock_t,Duration>& tp,
	   								std::basic_string<CharT, Traits, Alloc>* abbrev = nullptr, std::chrono::minutes* offset = nullptr) {
	using Clock = std::chrono::system_clock;
	using Type = impl::clock_t::rep;

	Clock::time_point tp_;
    date::from_stream(is, fmt, tp_, abbrev, offset);
	tp = impl::clock_t::from_sys<Clock::duration>(tp_);
    return is;
}


