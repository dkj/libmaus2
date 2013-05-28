/*
    libmaus
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

#if ! defined(HISTOGRAMSET_HPP)
#define HISTOGRAMSET_HPP

#include <libmaus/util/Histogram.hpp>

namespace libmaus
{
	namespace util
	{
		struct HistogramSet
		{
			typedef HistogramSet this_type;
			typedef ::libmaus::util::unique_ptr<this_type>::type unique_ptr_type;
			
			::libmaus::autoarray::AutoArray < Histogram::unique_ptr_type > H;
			
			HistogramSet(uint64_t const numhist, uint64_t const lowsize);
			
			Histogram & operator[](uint64_t const i)
			{
				return *(H[i]);
			}
			
			void print(std::ostream & out) const;
			Histogram::unique_ptr_type merge() const;
		};
	}
}
#endif
