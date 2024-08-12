﻿using CalculatorApp.Entities;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace CalculatorApp.Services
{
    public interface ICurrencyService
    {
        Task<Currency> GetCurrency(string currencyId);
        Task<List<Currency>> GetCurrencies();
    }
}
