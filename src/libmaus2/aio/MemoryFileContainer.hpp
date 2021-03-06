/*
    libmaus2
    Copyright (C) 2009-2015 German Tischler
    Copyright (C) 2011-2015 Genome Research Limited

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
#if ! defined(LIBMAUS2_AIO_MEMORYFILECONTAINER_HPP)
#define LIBMAUS2_AIO_MEMORYFILECONTAINER_HPP

#include <libmaus2/aio/MemoryFileAdapter.hpp>
#include <libmaus2/autoarray/AutoArray.hpp>
#include <libmaus2/parallel/PosixMutex.hpp>
#include <map>

namespace libmaus2
{
	namespace aio
	{
		struct MemoryFileContainer
		{
			typedef MemoryFileContainer this_type;
			typedef libmaus2::util::unique_ptr<this_type>::type unique_ptr_type;
			typedef libmaus2::util::shared_ptr<this_type>::type shared_ptr_type;
			
			static libmaus2::parallel::PosixMutex lock;
			static std::map < 
				std::string, MemoryFile::shared_ptr_type 
			> M;
			
			static MemoryFileAdapter::shared_ptr_type getEntry(std::string const & name)
			{
				libmaus2::parallel::ScopePosixMutex slock(lock);
				
				MemoryFile::shared_ptr_type memfile;
				
				std::map < std::string, MemoryFile::shared_ptr_type >::iterator ita = M.find(name);
				
				if ( ita != M.end() )
				{
					memfile = ita->second;
				}
				else
				{
					MemoryFile::shared_ptr_type tmemfile(new MemoryFile);
					M[name] = tmemfile;
					memfile = tmemfile;
				}
					
				MemoryFileAdapter::shared_ptr_type ptr(new MemoryFileAdapter(memfile));
				
				return ptr;
			}
			
			static void eraseEntry(std::string const & name)
			{				
				libmaus2::parallel::ScopePosixMutex slock(lock);

				std::map < std::string, MemoryFile::shared_ptr_type >::iterator ita = M.find(name);
				
				if ( ita != M.end() )
					M.erase(ita);
			}
		};
	}
}
#endif
