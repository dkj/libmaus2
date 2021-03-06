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
#if ! defined(LIBMAUS2_LZ_BGZFINFLATEZSTREAMBASE_HPP)
#define LIBMAUS2_LZ_BGZFINFLATEZSTREAMBASE_HPP

#include <zlib.h>
#include <libmaus2/autoarray/AutoArray.hpp>
#include <libmaus2/lz/BgzfConstants.hpp>
#include <libmaus2/lz/BgzfInflateHeaderBase.hpp>

namespace libmaus2
{
	namespace lz
	{
		struct BgzfInflateZStreamBase
		{
			typedef BgzfInflateZStreamBase this_type;
			typedef libmaus2::util::unique_ptr<this_type>::type unique_ptr_type;
			typedef libmaus2::util::shared_ptr<this_type>::type shared_ptr_type;
		
			z_stream inflatestrm;
		
			void zinit()
			{
				memset(&inflatestrm,0,sizeof(z_stream));
						
				inflatestrm.zalloc = Z_NULL;
				inflatestrm.zfree = Z_NULL;
				inflatestrm.opaque = Z_NULL;
				inflatestrm.avail_in = 0;
				inflatestrm.next_in = Z_NULL;
						
				int const ret = inflateInit2(&inflatestrm,-15);
							
				if (ret != Z_OK)
				{
					::libmaus2::exception::LibMausException se;
					se.getStream() << "BgzfInflate::init() failed in inflateInit2";
					se.finish();
					throw se;
				}
			}
			
			BgzfInflateZStreamBase()
			{
				zinit();
			}

			~BgzfInflateZStreamBase()
			{
				inflateEnd(&inflatestrm);				
			}
			
			void zreset()
			{
				if ( inflateReset(&inflatestrm) != Z_OK )
				{
					::libmaus2::exception::LibMausException se;
					se.getStream() << "BgzfInflate::decompressBlock(): inflateReset failed";
					se.finish();
					throw se;									
				}			
			}
			
			void zdecompress(
				uint8_t       * const in,
				unsigned int const inlen,
				char          * const out,
				unsigned int const outlen
			)
			{
				zreset();

				inflatestrm.avail_in = inlen;
				inflatestrm.next_in = in;
				inflatestrm.avail_out = outlen;
				inflatestrm.next_out = reinterpret_cast<Bytef *>(out);
								
				int const r = inflate(&inflatestrm,Z_FINISH);
				
				bool ok = (r == Z_STREAM_END)
				     && (inflatestrm.avail_out == 0)
				     && (inflatestrm.avail_in == 0);
				
				if ( !ok )
				{
					::libmaus2::exception::LibMausException se;
					se.getStream() << "BgzfInflate::decompressBlock(): inflate failed";
					se.finish();
					throw se;												
				}
			}
		};
	}
}
#endif
