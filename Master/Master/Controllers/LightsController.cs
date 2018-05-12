using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using Microsoft.AspNetCore.Mvc;
using RestSharp;

namespace Master.Controllers
{
    [Route("api/[controller]")]
    public class LightsController : Controller
    {
        const string ArduinoIp = "192.168.1.11";

        [HttpGet("{mode}")]
        public void Get(Power mode)
        {
            var client = new RestClient($"http://{ArduinoIp}");
            var request = new RestRequest($"power{mode}", Method.GET);

            client.Execute(request);
        }
    }
}
