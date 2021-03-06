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
#if ! defined(LIBMAUS2_BAMBAM_PARALLEL_CRAMENCODINGWORKPACKAGE_HPP)
#define LIBMAUS2_BAMBAM_PARALLEL_CRAMENCODINGWORKPACKAGE_HPP

#include <libmaus2/bambam/parallel/ScramCramEncoding.hpp>
#include <libmaus2/parallel/SimpleThreadWorkPackage.hpp>

namespace libmaus2
{
	namespace bambam
	{
		namespace parallel
		{
			
			struct CramEncodingWorkPackage : public libmaus2::parallel::SimpleThreadWorkPackage
			{
				typedef CramEncodingWorkPackage this_type;
				typedef libmaus2::util::unique_ptr<this_type>::type unique_ptr_type;
				typedef libmaus2::util::shared_ptr<this_type>::type shared_ptr_type;
				
				void * package;
				ScramCramEncoding * iolibInterface;
			
				CramEncodingWorkPackage() : libmaus2::parallel::SimpleThreadWorkPackage(), package(0), iolibInterface(0) {}
				CramEncodingWorkPackage(uint64_t const rpriority, uint64_t const rdispatcherid, void * rpackage, ScramCramEncoding * riolibInterface)
				: libmaus2::parallel::SimpleThreadWorkPackage(rpriority,rdispatcherid), package(rpackage), iolibInterface(riolibInterface)
				{
				
				}
				virtual ~CramEncodingWorkPackage() {}
				
				virtual char const * getPackageName() const
				{
					return "CramEncodingWorkPackage";
				}
				
				void dispatch()
				{
					int r;
					if ( (r=iolibInterface->cram_process_work_package(package)) )
					{
						libmaus2::exception::LibMausException lme;
						lme.getStream() << "CramEncodingWorkPackage::dispatch: cram_process_work_package returned error code " << r << std::endl;
						lme.finish();
						throw lme;
					}
				}
			};
		}
	}
}
#endif
