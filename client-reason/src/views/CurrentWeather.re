/* State declaration */
type state = {
  isLoading: bool,
  currentTemp: string,
  humidity: string,
  wind: string,
  windDirection: string,
  currentCondition: string,
  currentConditionDescription: string,
  weatherIcon: string,
  cityName: string,
  cityNotFound: string,
};

/* Action declaration */
type action =
  | NotFound
  | WeatherIcon;

/* Component template declaration.
   Needs to be **after** state and action declarations! */
let component = ReasonReact.reducerComponent("CurrentWeather");

/* greeting and children are props. `children` isn't used, therefore ignored.
   We ignore it by prepending it with an underscore */
let make =
    (
      ~isLoading,
      ~currentTemp,
      ~humidity,
      ~wind,
      ~windDirection,
      ~currentCondition,
      ~currentConditionDescription,
      ~weatherIcon,
      ~cityName,
      ~cityNotFound,
      _children,
    ) => {
  /* spread the other default fields of component here and override a few */
  ...component,
  initialState: () => {
    isLoading: true,
    currentTemp: "",
    humidity: "",
    wind: "",
    windDirection: "",
    currentCondition: "",
    currentConditionDescription: "",
    weatherIcon: "",
    cityName: "",
    cityNotFound: "",
  },
  didMount: self => {
    Js.Promise.(
        Fetch.fetch("/search-location-weather")
            |> then_(Fetch.Response.json)
            |> then_(data => {
                switch (data.data.cod) {
                    | "404" => self.send(NotFound)
                    | _ => {
                        let weatherId = data.data.weather[0].id;
                        
                        if (weatherId <= 232) {
                                    self.send(WeatherIcon({ weatherIcon: ThunderStormIcon }));
                                  } else if (weatherId >= 300 && weatherId <= 531) {
                                    self.send(WeatherIcon({ weatherIcon: RainIcon }));
                                  } else if (weatherId >= 600 && weatherId <= 622) {
                                    self.send(WeatherIcon({ weatherIcon: SnowIcon }));
                                  } else if (weatherId === 800) {
                                    self.send(WeatherIcon({ weatherIcon: ClearIcon }));
                                  } else if (weatherId >= 801 && weatherId <= 804) {
                                    self.send(WeatherIcon({ weatherIcon: CloudsIcon }));
                                  }

/* Convert this next */
this.setState({
            isLoading: false,
            currentTemp: Math.round(data.data.main.temp) + '°',
            humidity: data.data.main.humidity + '%',
            wind: Math.round(data.data.wind.speed) + ' mph',
            windDirection: data.data.wind.deg,
            currentCondition: data.data.weather[0].main,
            currentConditionDescription: data.data.weather[0].description,
            cityName: data.data.name,
          });

          /* Should be the end of converted, could catch the error */
                    }
                }
            })
    )
  }
    /* State transitions */
    reducer => (
    switch (action) {
    | NotFound => ReasonReact.Update({...state, isLoading: false, cityNotFound: "404" })
    | WeatherIcon(icon) => ReasonReact.Update({...state, weatherIcon: icon})
    }: (
      action,
      state,
    )
  ),
  render: self =>
    isLoading ?
      <div> <LoadingDisplay /> </div> :
      <div>
        <WeatherConditions
          currentTemp
          humidity
          wind
          windDirection
          currentCondition
          currentConditionDescription
          weatherIcon
          cityName
        />
      </div>,
};
