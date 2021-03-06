/*
    libmaus2
    Copyright (C) 2009-2013 German Tischler
    Copyright (C) 2011-2013 Genome Research Limited

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#if ! defined(LIBMAUS2_PARALLEL_LOCKEDBOOL_HPP)
#define LIBMAUS2_PARALLEL_LOCKEDBOOL_HPP

#include <libmaus2/parallel/OMPLock.hpp>

#if defined(LIBMAUS2_HAVE_POSIX_SPINLOCKS)
#include <libmaus2/parallel/PosixSpinLock.hpp>
#endif

namespace libmaus2
{
	namespace parallel
	{
		struct LockedBool
		{
			#if defined(LIBMAUS2_HAVE_POSIX_SPINLOCKS)
			libmaus2::parallel::PosixSpinLock lock;
			#else
			libmaus2::parallel::OMPLock lock;
			#endif
			volatile bool b;
			
			LockedBool(bool const rb)
			: b(rb)
			{
			}
			
			bool get()
			{
				bool rb;
				lock.lock();
				rb = b;
				lock.unlock();
				return rb;
			}
			
			void set(bool const rb)
			{
				lock.lock();
				b = rb;
				lock.unlock();
			}
		};
	}
}
#endif
