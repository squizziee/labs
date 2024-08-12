using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _253504Lianha.Application.CarUseCases.Queries
{
    public record GetAllCarsQuery : IRequest<List<Car>>
    {
    }
}
