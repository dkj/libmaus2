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
#if ! defined(LIBMAUS2_NETWORK_LOGRECEIVERTESTPROCESS_HPP)
#define LIBMAUS2_NETWORK_LOGRECEIVERTESTPROCESS_HPP

#include <libmaus2/network/LogReceiverDispatcherBase.hpp>
#include <libmaus2/parallel/PosixProcess.hpp>
#include <libmaus2/util/unique_ptr.hpp>
#include <libmaus2/util/shared_ptr.hpp>

namespace libmaus2
{
	namespace network
	{

		struct LogReceiverTestProcess : public ::libmaus2::parallel::PosixProcess, public LogReceiverDispatcherBase
		{
			typedef LogReceiverTestProcess this_type;
			typedef ::libmaus2::util::unique_ptr<this_type>::type unique_ptr_type;
			typedef ::libmaus2::util::shared_ptr<this_type>::type shared_ptr_type;
			
			
			std::string const sid;
			std::string const loghostname;
			unsigned short const port;
			uint64_t const id;
			std::vector<int> const closeFds;
			DispatchCallback * dc;
			
			static unique_ptr_type construct(
				std::string const & rsid, 
				std::string const & rloghostname, 
				unsigned short const rport, 
				uint64_t const rid, 
				std::vector<int> const & rcloseFds,
				DispatchCallback * dc)
			{
				unique_ptr_type ptr(new this_type(rsid,rloghostname,rport,rid,rcloseFds,dc));
				return UNIQUE_PTR_MOVE(ptr);
			}

			LogReceiverTestProcess(
				std::string const & rsid, 
				std::string const & rloghostname, 
				unsigned short const rport, 
				uint64_t const rid,
				std::vector<int> const & rcloseFds,
				DispatchCallback * rdc = 0
			)
			: sid(rsid), loghostname(rloghostname), port(rport), id(rid), closeFds(rcloseFds), dc(rdc)
			{
				start();
			}
			
			
			virtual int run()
			{
				for ( uint64_t i = 0; i < closeFds.size(); ++i )
					::close(closeFds[i]);

				std::vector<std::string> const args(1,std::string("testprocess"));
				::libmaus2::util::ArgInfo const arginfo(args);
				return dispatch(arginfo,sid,loghostname,port,id,dc);
			}
		};
	}
}
#endif
