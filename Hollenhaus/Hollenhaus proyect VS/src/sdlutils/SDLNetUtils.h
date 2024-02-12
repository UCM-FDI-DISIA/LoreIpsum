// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <iostream>
#include <SDL_net.h>
#include <cassert>

// start of macros
//
// some macros to define serialization automatically.
//
// _IMPL_SERIALIAZION_(a,b,c,...)
//
//   define method serialize and deserialize for attributes,
//   a,b and c.
//
// _IMPL_SERIALIAZION_WITH_BASE_(T,a,b,c,...)
//
//   define method serialize and deserialize for attributes,
//   a,b and c. But they will be preceded by a call to
//   T::serialize(buf) and T::deserialize(buf) respectively. This
//   should be used in derived structs to serialize base structs
//   first
//
//
#define _IMPL_SERIALIAZION_(...) \
	inline Uint8* serialize(Uint8 *buf) {\
		buf = SDLNetUtils::serialize_all(buf, __VA_ARGS__);\
		return buf;\
	}\
	inline Uint8* deserialize(Uint8 *buf) {\
		buf = SDLNetUtils::deserialize_all(buf,__VA_ARGS__);\
		return buf;\
	}

#define _IMPL_SERIALIAZION_WITH_BASE_(T,...) \
	inline Uint8* serialize(Uint8 *buf) {\
		buf = T::serialize(buf);\
		buf = SDLNetUtils::serialize_all(buf, __VA_ARGS__);\
		return buf;\
	}\
	inline Uint8* deserialize(Uint8 *buf) {\
		buf = T::deserialize(buf);\
		buf = SDLNetUtils::deserialize_all(buf,__VA_ARGS__);\
		return buf;\
	}

// end of macros

class SDLNetUtils {

	using msgSize_t = Uint16;
	static constexpr std::size_t bufferSize_ = 1024;
	static Uint8 buffer[bufferSize_];

public:

	/*
	 * Initialize SDL
	 */
	inline static void initSDLNet() {
		if (SDLNet_Init() < 0) {
			print_SDLNet_error_and_exit();
		}
	}

	/*
	 * Close SDLNet
	 */
	inline static void closeSDLNet() {
		SDLNet_Quit();
	}

	/*
	 * Print the SDL error
	 */
	inline static void print_SDLNet_error() {
		std::cout << "Error: " << SDLNet_GetError() << std::endl;
	}

	/*
	 * Print the SDL error and exit
	 */
	inline static void print_SDLNet_error_and_exit(int code = 1) {
		print_SDLNet_error();
		exit(code);
	}

	/*
	 *  print an IPv4 given as Uin32
	 */
	inline static void print_ip(Uint32 ip, bool newline = false) {
		std::cout << (ip & 0xFF) << "." //
				<< ((ip >> 8) & 0xFF) << "." //
				<< ((ip >> 16) & 0xFF) << "." //
				<< ((ip >> 24) & 0xFF);
		if (newline)
			std::cout << std::endl;
	}

	/*
	 *  print an IPaddress
	 */
	inline static void print_ip(IPaddress ip, bool newline = false) {
		print_ip(ip.host, false);
		std::cout << ":" << sdlnet_ntoh(ip.port);
		if (newline)
			std::cout << std::endl;
	}

	/*
	 * Return the local port associated to a socket
	 */
	inline static Uint16 getSocketPort(UDPsocket sock) {
		return sdlnet_ntoh(SDLNet_UDP_GetPeerAddress(sock, -1)->port);
	}

	inline static Uint16 getSocketPort(TCPsocket sock) {
		return sdlnet_ntoh(SDLNet_TCP_GetPeerAddress(sock)->port);
	}

	/*
	 * Convert between host and network endianness
	 *
	 * sdlnet_hton: converts from host endianness to network endianness
	 * sdlnet_ntoh: converts from network endianness to host endianness
	 *
	 * They are implemented for Uint32, Uint16n and Uint8 (obviously Uint8
	 * is not needed, it is just for compatibility of some code that uses
	 * templates.
	 *
	 */

	inline static Uint32 sdlnet_hton(Uint32 v) {
		Uint32 nv;
		SDLNet_Write32(v, &nv);
		return nv;
	}

	inline static Uint32 sdlnet_ntoh(Uint32 nv) {
		return SDLNet_Read32(&nv);
	}

	inline static Uint16 sdlnet_hton(Uint16 v) {
		Uint16 nv;
		SDLNet_Write16(v, &nv);
		return nv;
	}

	inline static Uint16 sdlnet_ntoh(Uint16 nv) {
		return SDLNet_Read16(&nv);
	}

	inline static Uint8 sdlnet_hton(Uint8 v) {
		return v;
	}

	inline static Uint8 sdlnet_ntoh(Uint8 nv) {
		return nv;
	}

	/**
	 *  SERIALIZATION and DESERIALIZATION of FIXED LENGTH TYPES
	 *
	 */

	// serializing a list of arguments (automatically calls
	// serialize for each one)
	template<typename ...Ts>
	static inline Uint8* serialize_all(Uint8 *buf, Ts &...args) {
		((buf = serialize(args, buf)),...);
		return buf;
	}

	// deserializing a list of arguments (automatically calls
	// deserialize for each one)
	template<typename ...Ts>
	static inline Uint8* deserialize_all(Uint8 *buf, Ts &...args) {
		((buf = deserialize(args, buf)),...);
		return buf;
	}

	// when v is a struct we use its own serialize/deserialize
	template<typename T>
	inline static Uint8* serialize(T &v, Uint8 *buf) {
		return v.serialize(buf);
	}

	template<typename T>
	inline static Uint8* deserialize(T &v, Uint8 *buf) {
		return v.deserialize(buf);
	}

	// when v is of type T[N] we use serialize_array/deserialize_array
	template<typename T, std::size_t N>
	inline static Uint8* serialize(T (&v)[N], Uint8 *buf) {
		return serialize_array(v, N, buf);
	}

	template<typename T, std::size_t N>
	inline static Uint8* deserialize(T (&v)[N], Uint8 *buf) {
		return deserialize_array(v, N, buf);
	}

	// case for char, it is treated as if it where Uint8. Use
	// it only to send/receive chars with non-negative values, i.e.,
	// ASCII codes
	template<>
	inline static Uint8* serialize<char>(char &v, Uint8 *buf) {
		Uint8 &aux_v = reinterpret_cast<Uint8&>(v);
		return serialize_uint(aux_v, buf);
	}

	// cases for unsigned integer, we delegate to serialize_uint and
	// deserialize_uint

	template<>
	inline static Uint8* deserialize<char>(char &v, Uint8 *buf) {
		Uint8 &aux_v = reinterpret_cast<Uint8&>(v);
		return deserialize_uint(aux_v, buf);
	}

	// case for Uint8
	template<>
	inline static Uint8* serialize<Uint8>(Uint8 &v, Uint8 *buf) {
		return serialize_uint(v, buf);
	}

	template<>
	inline static Uint8* deserialize<Uint8>(Uint8 &v, Uint8 *buf) {
		return deserialize_uint(v, buf);
	}

	// case for Uint16
	template<>
	inline static Uint8* serialize<Uint16>(Uint16 &v, Uint8 *buf) {
		return serialize_uint(v, buf);
	}

	template<>
	inline static Uint8* deserialize<Uint16>(Uint16 &v, Uint8 *buf) {
		return deserialize_uint(v, buf);
	}

	// case for Uint32
	template<>
	inline static Uint8* serialize<Uint32>(Uint32 &v, Uint8 *buf) {
		return serialize_uint(v, buf);
	}

	template<>
	inline static Uint8* deserialize<Uint32>(Uint32 &v, Uint8 *buf) {
		return deserialize_uint(v, buf);
	}

	// cases for signed integer, we delegate to serialize_sint and
	// deserialize_sint

	// case for Sint8
	template<>
	inline static Uint8* serialize<Sint8>(Sint8 &v, Uint8 *buf) {
		return serialize_sint<Uint8>(v, buf);
	}

	template<>
	inline static Uint8* deserialize<Sint8>(Sint8 &v, Uint8 *buf) {
		return deserialize_sint<Uint8>(v, buf);
	}

	// case for Sint16
	template<>
	inline static Uint8* serialize<Sint16>(Sint16 &v, Uint8 *buf) {
		return serialize_sint<Uint16>(v, buf);
	}

	template<>
	inline static Uint8* deserialize<Sint16>(Sint16 &v, Uint8 *buf) {
		return deserialize_sint<Uint16>(v, buf);
	}

	// case for Sint32
	template<>
	inline static Uint8* serialize<Sint32>(Sint32 &v, Uint8 *buf) {
		return serialize_sint<Uint32>(v, buf);
	}

	template<>
	inline static Uint8* deserialize<Sint32>(Sint32 &v, Uint8 *buf) {
		return deserialize_sint<Uint32>(v, buf);
	}

	// float
	//
	// Treating the 4 bytes as Uint32 and serialize it, should work
	// fine for our needs. We could transmit the sign, mantissa, and
	// exponent
	//
	template<>
	inline static Uint8* serialize<float>(float &v, Uint8 *buf) {
		static_assert( sizeof(float) == 4, "float is not 32 bits");
		return serialize(reinterpret_cast<Uint32&>(v), buf);
	}
	template<>
	inline static Uint8* deserialize<float>(float &v, Uint8 *buf) {
		static_assert( sizeof(float) == 4, "float is not 32 bits");
		return deserialize(reinterpret_cast<Uint32&>(v), buf);
	}

	// (de)serialization of arrays is done, by default, by calling the serialize/deserialize on
	// each element. There are special cases for 1-byte types to use memcpy (they
	// call serialize_arraybyte that is defined in the private section below)
	//
	template<typename T>
	inline static Uint8* serialize_array(T *v, std::size_t N, Uint8 *buf) {
		static_assert ( !std::is_compound_v<T> );
		for (auto i = 0u; i < N; i++)
			buf = serialize(v[i], buf);
		return buf;
	}

	template<typename T>
	inline static Uint8* deserialize_array(T *v, std::size_t N, Uint8 *buf) {
		static_assert ( !std::is_compound_v<T> );
		for (auto i = 0u; i < N; i++)
			buf = deserialize(v[i], buf);
		return buf;
	}

	// case for char, we copy as if it were bytes, ignoring the sign. This
	// should be used only for char* that are C-string
	template<>
	inline static Uint8* serialize_array<char>(char *v, std::size_t N,
			Uint8 *buf) {
		return serialize_arraybyte(reinterpret_cast<Uint8*>(v), N, buf);
	}

	template<>
	inline static Uint8* deserialize_array<char>(char *v, std::size_t N,
			Uint8 *buf) {
		return deserialize_arraybyte(reinterpret_cast<Uint8*>(v), N, buf);
	}

	// case for array of Uint8
	template<>
	inline static Uint8* serialize_array<Uint8>(Uint8 *v, std::size_t N,
			Uint8 *buf) {
		return serialize_arraybyte(reinterpret_cast<Uint8*>(v), N, buf);
	}

	template<>
	inline static Uint8* deserialize_array<Uint8>(Uint8 *v, std::size_t N,
			Uint8 *buf) {
		return deserialize_arraybyte(reinterpret_cast<Uint8*>(v), N, buf);
	}

	/*
	 * Send/Receive messages for TCP. The purpose is to add a header to
	 * the message indicating its size, so the other size can read it
	 * correctly. The users do not receive back this size, they should identify
	 * their data by other means.
	 *
	 */

	// send a message (msgSize bytes starting at  v) in a TCP socket with
	// a header indicating its size, so it can be read completely at the
	// other end
	//
	// We assume the called is aware of the buffer size defined below as buffSize_
	//
	// returns true if the message was sent correctly, otherwise false
	//
	inline static bool send(Uint8 *v, TCPsocket sock, msgSize_t msgSize) {

		assert(msgSize <= bufferSize_);

		int result = 0;

		// convert the size to network endianness
		msgSize_t size = sdlnet_hton(msgSize);

		// send the size as a header
		result = SDLNet_TCP_Send(sock, reinterpret_cast<Uint8*>(&size),
				sizeof(msgSize_t));

		if (result != sizeof(msgSize_t))
			return false;

		// send the message itself
		result = SDLNet_TCP_Send(sock, v, msgSize);

		return result == msgSize;
	}

	// receive a message that was send by method 'send' above, i.e., with
	// the size as a header.
	//
	// returns a pointer to the buffer where the message is stored, or nullptr
	// if something went wring.
	//
	// We don't return the size, the user should identify the message by other means
	//
	inline static Uint8* receiveMsg(TCPsocket sock) {

		int result = 0;

		// read the size of the message, the first sizeof(msgSize_t) bytes, into buffer
		result = SDLNet_TCP_Recv(sock, buffer, sizeof(msgSize_t));
		if (result != sizeof(msgSize_t))
			return nullptr;

		// convert size from network endianness to host endianness
		Uint16 size = sdlnet_ntoh(*reinterpret_cast<msgSize_t*>(buffer));

		assert(size <= bufferSize_);

		// receive size bytes
		auto bytesRead = 0;
		while (bytesRead < size) {
			result = SDLNet_TCP_Recv(sock, buffer + bytesRead,
					size - bytesRead);
			if (result < 1)
				return nullptr;
			bytesRead += result;
		}

		return buffer;
	}

	// Send a message using serialization, assuming the struct T has a method
	// serialize.
	//
	// returns true if the message was sent correctly, otherwise false
	//
	template<typename T>
	inline static bool serializedSend(T &v, TCPsocket sock) {

		// serialize the message into the buffer, it returns
		// a pointer to the cell after the buffer. We assume
		// the caller knows that the buffer size if bufferSize_
		Uint8 *end = v.serialize(buffer);
		msgSize_t msgSize = end - buffer;

		// convert to network endianness
		Uint16 size = sdlnet_hton(msgSize);
		assert(size <= bufferSize_);

		// send the message size as the header
		auto result = SDLNet_TCP_Send(sock, reinterpret_cast<Uint8*>(&size),
				sizeof(msgSize_t));
		if (result != sizeof(msgSize_t))
			return false;

		// send the message itself
		result = SDLNet_TCP_Send(sock, buffer, msgSize);

		return result == msgSize;
	}

	// Receive a message that was sent serializedSend (or send) using deserialization,
	// assuming the struct T has a deserialize method.
	//
	// returns true if the message was received correctly, otherwise false
	//
	template<typename T>
	inline static bool deserializedReceive(T &v, TCPsocket sock) {
		Uint8 *msg = receiveMsg(sock);
		if (msg == nullptr)
			return false;
		else {
			v.deserialize(msg);
			return true;
		}
	}

	/*
	 * Send/Receive messages for UDP for types that implement
	 * serialize and deserialize
	 */

	template<typename T>
	inline static int serializedSend(T &m, UDPpacket *p, UDPsocket sock) {
		Uint8 *end = m.serialize(p->data);
		p->len = end - p->data;
		return SDLNet_UDP_Send(sock, -1, p);
	}

	template<typename T>
	inline static int serializedSend(T &m, UDPpacket *p, UDPsocket sock,
			const IPaddress &ip) {
		p->address = ip;
		return serializedSend(m, p, sock);
	}

	template<typename T>
	inline static int deserializedReceive(T &m, UDPpacket *p, UDPsocket sock) {
		int status = 0;
		if ((status = SDLNet_UDP_Recv(sock, p)) > 0) {
			m.deserialize(p->data);
		}
		return status;
	}

private:

	// serializing an unsigned integer typed
	template<typename UnsignedT>
	inline static Uint8* serialize_uint(UnsignedT &v, Uint8 *buf) {
		*reinterpret_cast<UnsignedT*>(buf) = sdlnet_hton(v);
		return buf + sizeof(UnsignedT);
	}

	template<typename UnsignedT>
	inline static Uint8* deserialize_uint(UnsignedT &v, Uint8 *buf) {
		v = sdlnet_ntoh(*reinterpret_cast<UnsignedT*>(buf));
		return buf + sizeof(UnsignedT);
	}

	/** signed integer **/

	// if both use the same representation, e.g., two's complement, just treat
	// it as the corresponding unsigned type
	template<typename UnsignedT, typename SignedT>
	inline static Uint8* serialize_sint(SignedT &v, Uint8 *buf) {
		return serialize_uint<UnsignedT>(reinterpret_cast<UnsignedT&>(v), buf);
	}

	template<typename UnsignedT, typename SignedT>
	inline static Uint8* deserialize_sint(SignedT &v, Uint8 *buf) {
		return deserialize_uint<UnsignedT>(reinterpret_cast<UnsignedT&>(v), buf);
	}

	// if there is a risk that the different sides use different representations,
	// then better transmit the sign separately
	//
//	template<typename UnsignedT, typename SignedT>
//	inline static Uint8* serialize_sint(SignedT &v, Uint8 *buf) {
//		static_assert( sizeof(UnsignedT) == sizeof(SignedT), "Signed and unsigned types do not match" );
//		Uint8 sign;
//		UnsignedT abs_v;
//
//		if (v >= 0) {
//			abs_v = v;
//			sign = 0;
//		} else {
//			abs_v = -v;
//			sign = 1;
//		}
//
//		UnsignedT abs_nv = sdlnet_hton(abs_v);
//		*reinterpret_cast<Uint8*>(buf) = sign;
//		*reinterpret_cast<UnsignedT*>(buf + 1) = abs_nv;
//
//		return buf + sizeof(UnsignedT) + 1;
//	}
//
//	template<typename UnsignedT, typename SignedT>
//	inline static Uint8* deserialize_sint(SignedT &v, Uint8 *buf) {
//		static_assert( sizeof(UnsignedT) == sizeof(SignedT), "Signed and unsigned types do not match" );
//		Uint8 sign = *reinterpret_cast<Uint8*>(buf);
//		UnsignedT abs_nv = *reinterpret_cast<UnsignedT*>(buf + 1);
//		UnsignedT abs_v = sdlnet_ntoh(abs_nv);
//
//		if (sign == 0) {
//			v = abs_v;
//		} else {
//			v = -static_cast<SignedT>(abs_v);
//		}
//
//		return buf + sizeof(UnsignedT) + 1;
//	}

	// serializing array of bytes
	inline static Uint8* serialize_arraybyte(Uint8 *v, std::size_t N,
			Uint8 *buf) {
		memcpy(buf, v, N);
		return buf + N;
	}

	inline static Uint8* deserialize_arraybyte(Uint8 *v, std::size_t N,
			Uint8 *buf) {
		memcpy(v, buf, N);
		return buf + N;
	}

};
