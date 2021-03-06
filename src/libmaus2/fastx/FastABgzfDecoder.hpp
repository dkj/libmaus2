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
#if !defined(LIBMAUS2_FASTX_FASTABGZFDECODER_HPP)
#define LIBMAUS2_FASTX_FASTABGZFDECODER_HPP

#include <libmaus2/fastx/FastABgzfDecoderBuffer.hpp>
#include <string>

namespace libmaus2
{
	namespace fastx
	{
		struct FastABgzfDecoder : public ::libmaus2::fastx::FastABgzfDecoderBuffer, public ::std::istream
		{
			typedef FastABgzfDecoder this_type;
			typedef ::libmaus2::util::unique_ptr<this_type>::type unique_ptr_type;
			typedef ::libmaus2::util::shared_ptr<this_type>::type shared_ptr_type;
		
			FastABgzfDecoder(
				std::string const & filename,
				::libmaus2::fastx::FastABgzfIndexEntry const & indexentry,
				uint64_t const blocksize
			)
			: ::libmaus2::fastx::FastABgzfDecoderBuffer(filename,indexentry,blocksize), ::std::istream(this)
			{
				
			}
			FastABgzfDecoder(
				std::istream & stream,
				::libmaus2::fastx::FastABgzfIndexEntry const & indexentry,
				uint64_t const blocksize
			)
			: ::libmaus2::fastx::FastABgzfDecoderBuffer(stream,indexentry,blocksize), ::std::istream(this)
			{
				
			}
		};

	}
}
#endif
