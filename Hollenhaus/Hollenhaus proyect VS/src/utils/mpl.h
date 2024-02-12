// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <cstddef>
#include <cstdint>
#include <limits>
#include <type_traits>
#include <cstdlib>

namespace mpl {

// Compile-time list of types.
template<typename ... Ts>
struct TypeList {
	// Size of the list.
	static constexpr std::size_t size { sizeof...(Ts) };
};

// IndexOf<T,TypeList<T1,T2,...>>() is the position of T in T1,T2,...
// could also use <T,TypeList<T1,T2,...>>::value
//
template<typename, typename >
struct IndexOf;

// IndexOf base case: found the type we're looking for.
template<typename T, typename ... Ts>
struct IndexOf<T, TypeList<T, Ts...>> : std::integral_constant<std::size_t, 0> {
};

// IndexOf recursive case: 1 + IndexOf the rest of the types.
template<typename T, typename ...Ts1, typename ... Ts>
struct IndexOf<T, TypeList<TypeList<T, Ts1...>, Ts...>> : std::integral_constant<
		std::size_t, 0> {
};

// IndexOf recursive case: 1 + IndexOf the rest of the types.
template<typename T, typename TOther, typename ...Ts1, typename ... Ts>
struct IndexOf<T, TypeList<TypeList<TOther, Ts1...>, Ts...>> : std::integral_constant<
		std::size_t, IndexOf<T, TypeList<TypeList<Ts1...>, Ts...>> { }> {
};

// IndexOf recursive case: 1 + IndexOf the rest of the types.
template<typename T, typename TOther, typename ... Ts>
struct IndexOf<T, TypeList<TOther, Ts...>> : std::integral_constant<std::size_t,
		1 + IndexOf<T, TypeList<Ts...>> { }> {
};

// Ith<i,TypeList<T1,T2,...>>::type is the type Ti
//
template<std::size_t i, typename >
struct Ith;

// Ith base case: the type is the first in the list
template<typename T, typename ... Ts>
struct Ith<0, TypeList<T, Ts...>> {
	using type = T;
};

// Ith recursive case: the type is the (i-1)th in the rest of the list
template<std::size_t i, typename T, typename ... Ts>
struct Ith<i, TypeList<T, Ts...>> {
	using type = typename Ith<i - 1, TypeList<Ts...>>::type;
};

// RemovePrefix<i,TypeList<T1,T2,...>>::type is TypeList<T_{i+1},T_{i+2},...>
//
// Ith<i,TypeList<T1,T2,...>>::type is the type Ti
//
template<std::size_t i, typename >
struct RemovePrefix;

// Ith base case: nothing to reemove
template<typename T, typename ... Ts>
struct RemovePrefix<0, TypeList<T, Ts...>> {
	using type = TypeList<T, Ts...>;
};

// Ith recursive case: remove the (i-1)th prefix from in the rest of the list
template<std::size_t i, typename T, typename ... Ts>
struct RemovePrefix<i, TypeList<T, Ts...>> {
	using type = typename RemovePrefix<i - 1, TypeList<Ts...>>::type;
};

// if T1 a complete type, i.e., not a forward declaration, then
// the field 'type' will be T1, otherwise T2
//
template<class T1, class T2, class = void>
struct is_complete_type {
	using type = T2;
};

template<class T1, class T2>
struct is_complete_type<T1, T2,
		std::enable_if_t<
				std::is_object<T1>::value && !std::is_pointer<T1>::value
						&& (sizeof(T1) > 0)> > {
	using type = T1;
};

// numeric_type<max>::type is an unsigned integer type large enough to
// hold the number max
//
template<std::size_t max, class = void>
struct numeric_type;

template<std::size_t max>
struct numeric_type<max,
		std::enable_if_t<(std::numeric_limits<uint8_t>::max() >= max)> > {
	using type = uint8_t;
};

template<std::size_t max>
struct numeric_type<max,
		std::enable_if_t<
				(std::numeric_limits<uint16_t>::max() >= max)
						&& (std::numeric_limits<uint8_t>::max() < max)> > {
	using type = uint16_t;
};

template<std::size_t max>
struct numeric_type<max,
		std::enable_if_t<
				(std::numeric_limits<uint32_t>::max() >= max)
						&& (std::numeric_limits<uint16_t>::max() < max)> > {
	using type = uint32_t;
};

}
