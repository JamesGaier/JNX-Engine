/// @ref gtx_vector_query
/// @file glm/gtx/vector_query.inl

#include <cassert>

namespace glm {
	namespace detail {
		template <typename T, precision P, template <typename, precision> class vecType>
		struct compute_areCollinear {};

		template <typename T, precision P>
		struct compute_areCollinear<T, P, tvec2> {
			GLM_FUNC_QUALIFIER static bool call(tvec2<T, P> const & v0, tvec2<T, P> const & v1, T const & epsilon) {
				return length(cross(tvec3<T, P>(v0, static_cast<T>(0)), tvec3<T, P>(v1, static_cast<T>(0)))) < epsilon;
			}
		};

		template <typename T, precision P>
		struct compute_areCollinear<T, P, tvec3> {
			GLM_FUNC_QUALIFIER static bool call(tvec3<T, P> const & v0, tvec3<T, P> const & v1, T const & epsilon) {
				return length(cross(v0, v1)) < epsilon;
			}
		};

		template <typename T, precision P>
		struct compute_areCollinear<T, P, tvec4> {
			GLM_FUNC_QUALIFIER static bool call(tvec4<T, P> const & v0, tvec4<T, P> const & v1, T const & epsilon) {
				return length(cross(tvec3<T, P>(v0), tvec3<T, P>(v1))) < epsilon;
			}
		};

		template <typename T, precision P, template <typename, precision> class vecType>
		struct compute_isCompNull {};

		template <typename T, precision P>
		struct compute_isCompNull<T, P, tvec2> {
			GLM_FUNC_QUALIFIER static tvec2<bool, P> call(tvec2<T, P> const & v, T const & epsilon) {
				return tvec2<bool, P>(
					(abs(v.x) < epsilon),
					(abs(v.y) < epsilon));
			}
		};

		template <typename T, precision P>
		struct compute_isCompNull<T, P, tvec3> {
			GLM_FUNC_QUALIFIER static tvec3<bool, P> call(tvec3<T, P> const & v, T const & epsilon) {
				return tvec3<bool, P>(
					(abs(v.x) < epsilon),
					(abs(v.y) < epsilon),
					(abs(v.z) < epsilon));
			}
		};

		template <typename T, precision P>
		struct compute_isCompNull<T, P, tvec4> {
			GLM_FUNC_QUALIFIER static tvec4<bool, P> call(tvec4<T, P> const & v, T const & epsilon) {
				return tvec4<bool, P>(
					(abs(v.x) < epsilon),
					(abs(v.y) < epsilon),
					(abs(v.z) < epsilon),
					(abs(v.w) < epsilon));
			}
		};
	}//namespace detail

	template <typename T, precision P, template <typename, precision> class vecType>
	GLM_FUNC_QUALIFIER bool areCollinear
	(
		vecType<T, P> const & v0,
		vecType<T, P> const & v1,
		T const & epsilon
	) {
		GLM_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'areCollinear' only accept floating-point inputs");

		return detail::compute_areCollinear<T, P, vecType>::call(v0, v1, epsilon);
	}

	template <typename T, precision P, template <typename, precision> class vecType>
	GLM_FUNC_QUALIFIER bool areOrthogonal
	(
		vecType<T, P> const & v0,
		vecType<T, P> const & v1,
		T const & epsilon
	) {
		GLM_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'areOrthogonal' only accept floating-point inputs");

		return abs(dot(v0, v1)) <= max(
			static_cast<T>(1),
			length(v0)) * max(static_cast<T>(1), length(v1)) * epsilon;
	}

	template <typename T, precision P, template <typename, precision> class vecType>
	GLM_FUNC_QUALIFIER bool isNormalized
	(
		vecType<T, P> const & v,
		T const & epsilon
	) {
		GLM_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'isNormalized' only accept floating-point inputs");

		return abs(length(v) - static_cast<T>(1)) <= static_cast<T>(2) * epsilon;
	}

	template <typename T, precision P, template <typename, precision> class vecType>
	GLM_FUNC_QUALIFIER bool isNull
	(
		vecType<T, P> const & v,
		T const & epsilon
	) {
		GLM_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'isNull' only accept floating-point inputs");

		return length(v) <= epsilon;
	}

	template <typename T, precision P, template <typename, precision> class vecType>
	GLM_FUNC_QUALIFIER vecType<bool, P> isCompNull
	(
		vecType<T, P> const & v,
		T const & epsilon
	) {
		GLM_STATIC_ASSERT(std::numeric_limits<T>::is_iec559, "'isCompNull' only accept floating-point inputs");

		return detail::compute_isCompNull<T, P, vecType>::call(v, epsilon);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec2<bool, P> isCompNull
	(
		tvec2<T, P> const & v,
		T const & epsilon) {
		return tvec2<bool, P>(
			abs(v.x) < epsilon,
			abs(v.y) < epsilon);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec3<bool, P> isCompNull
	(
		tvec3<T, P> const & v,
		T const & epsilon
	) {
		return tvec3<bool, P>(
			abs(v.x) < epsilon,
			abs(v.y) < epsilon,
			abs(v.z) < epsilon);
	}

	template <typename T, precision P>
	GLM_FUNC_QUALIFIER tvec4<bool, P> isCompNull
	(
		tvec4<T, P> const & v,
		T const & epsilon
	) {
		return tvec4<bool, P>(
			abs(v.x) < epsilon,
			abs(v.y) < epsilon,
			abs(v.z) < epsilon,
			abs(v.w) < epsilon);
	}

	template <typename T, precision P, template <typename, precision> class vecType>
	GLM_FUNC_QUALIFIER bool areOrthonormal
	(
		vecType<T, P> const & v0,
		vecType<T, P> const & v1,
		T const & epsilon
	) {
		return isNormalized(v0, epsilon) && isNormalized(v1, epsilon) && (abs(dot(v0, v1)) <= epsilon);
	}
}//namespace glm
