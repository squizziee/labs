using Microsoft.Extensions.DependencyInjection;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _253504Lianha.Application
{
	public static class DbInitializer
	{
		public static async Task Initialize(IServiceProvider services)
		{
			var unitOfWork = services.GetRequiredService<IUnitOfWork>();
			await unitOfWork.DeleteDataBaseAsync();
			await unitOfWork.CreateDataBaseAsync();

			await unitOfWork.CarRepository.AddAsync(new Car(1, "Porsche 919 Hybrid Evo 2018", "Germany", "Sequential", 2018));
			await unitOfWork.CarRepository.AddAsync(new Car(2, "Vector W8", "USA", "Manual", 1989));
			await unitOfWork.CarRepository.AddAsync(new Car(3, "DeTomaso Pantera", "USA", "Manual", 1970));

			await unitOfWork.SaveAllAsync();


			await unitOfWork.AdvertisementRepository.AddAsync(
				new Advertisement(
					1, 
					"Porsche sale", 
					new DateTime(2024, 6, 14), 
					"Faster than F1",
                    "C:\\Users\\USER\\Desktop\\cstemp\\LAB5\\253504Lianha.UI\\253504Lianha.UI\\Resources\\Images\\porsche919.jpg", 
					1, 
					12000000)
				);
            await unitOfWork.AdvertisementRepository.AddAsync(
                new Advertisement(
                    2,
                    "Porsche 919 sale",
                    new DateTime(2024, 6, 14),
                    "V4 with two electric motors, MGU-K deployment",
                    "C:\\Users\\USER\\Desktop\\cstemp\\LAB5\\253504Lianha.UI\\253504Lianha.UI\\Resources\\Images\\porsche919_2.jpeg",
                    1,
                    9500000)
				);
            await unitOfWork.AdvertisementRepository.AddAsync(
                new Advertisement(
                    3,
                    "Porsche sale crashed",
                    new DateTime(2024, 6, 14),
                    "Crashed prototype",
                    "C:\\Users\\USER\\Desktop\\cstemp\\LAB5\\253504Lianha.UI\\253504Lianha.UI\\Resources\\Images\\porsche919_3.jpg",
                    1,
                    5000000)
				);


            await unitOfWork.AdvertisementRepository.AddAsync(
                new Advertisement(
                    4,
                    "Old W8 classic sale",
                    new DateTime(2024, 6, 14),
                    "Crazy rare car",
                    "C:\\Users\\USER\\Desktop\\cstemp\\LAB5\\253504Lianha.UI\\253504Lianha.UI\\Resources\\Images\\vectorw8.jpg",
                    2,
                    7000000)
                );
            await unitOfWork.AdvertisementRepository.AddAsync(
                new Advertisement(
                    5,
                    "Vector W8 sale",
                    new DateTime(2024, 6, 14),
                    "Practically new car",
                    "C:\\Users\\USER\\Desktop\\cstemp\\LAB5\\253504Lianha.UI\\253504Lianha.UI\\Resources\\Images\\vectorw8_2.jpg",
                    2,
                    9750000)
                );


            await unitOfWork.AdvertisementRepository.AddAsync(
                new Advertisement(
                    6,
                    "DeTomaso sale",
                    new DateTime(2019, 1, 1),
                    "Pantera, the OG",
                    "C:\\Users\\USER\\Desktop\\cstemp\\LAB5\\253504Lianha.UI\\253504Lianha.UI\\Resources\\Images\\detomaso.jpg",
                    3,
                    2000000)
                );
            await unitOfWork.AdvertisementRepository.AddAsync(
                new Advertisement(
                    7,
                    "DeTomaso Pantera sale",
                    new DateTime(2022, 7, 18),
                    "Got couple scratches, nothing major",
                    "C:\\Users\\USER\\Desktop\\cstemp\\LAB5\\253504Lianha.UI\\253504Lianha.UI\\Resources\\Images\\detomaso2.jpg",
                    3,
                    700000)
                );
            await unitOfWork.AdvertisementRepository.AddAsync(
                new Advertisement(
                    8,
                    "Old DeTomaso sale sale",
                    new DateTime(2023, 4, 12),
                    "New car, 1000km mileage",
                    "C:\\Users\\USER\\Desktop\\cstemp\\LAB5\\253504Lianha.UI\\253504Lianha.UI\\Resources\\Images\\detomaso3.jpeg",
                    3,
                    1200000)
                );

            await unitOfWork.SaveAllAsync();
		}
	}
}
