import React, { Component } from 'react';
import { Link } from 'react-router-dom';
import { default as fetch } from 'isomorphic-fetch';

// Assets
import ThunderStormIcon from './assets/weather_icons/01W.svg';
import RainIcon from './assets/weather_icons/02W.svg';
import SnowIcon from './assets/weather_icons/03W.svg';
import ClearIcon from './assets/weather_icons/04W-DAY.svg';
import CloudsIcon from './assets/weather_icons/05W.svg';
import NoLocationFound from './assets/no-location.svg';
import LoadingIcon from './assets/loading.svg';

class CurrentWeather extends Component {
  constructor(props) {
    super(props);

    this.state = ({
      isLoading: true,
      currentTemp: '',
      humidity: '',
      wind: '',
      windDirection: '',
      currentCondition: '',
      currentConditionDescription: '',
      weatherIcon: '',
      cityName: '',
      cityNotFound: '',
    });
  }

  componentDidMount() {
    fetch('/search-location-weather/20120')
      .then(res => res.json())
      .then(data => {
        if (data.data.cod === '404') {
          this.setState({
            isLoading: false,
            cityNotFound: 404,
          });
        } else {
          // Determine weather icon
          let weatherId = data.data.weather[0].id;

          if (weatherId <= 232) {
            this.setState({ weatherIcon: ThunderStormIcon });
          } else if (weatherId >= 300 && weatherId <= 531) {
            this.setState({ weatherIcon: RainIcon });
          } else if (weatherId >= 600 && weatherId <= 622) {
            this.setState({ weatherIcon: SnowIcon });
          } else if (weatherId === 800) {
            this.setState({ weatherIcon: ClearIcon });
          } else if (weatherId >= 801 && weatherId <= 804) {
            this.setState({ weatherIcon: CloudsIcon });
          }

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
        }
      })
      .catch(err => {
        console.log(err);
      });
  }

}

export default CurrentWeather;
