FROM microsoft/aspnetcore:2.0 AS base
WORKDIR /app
EXPOSE 80

FROM microsoft/aspnetcore-build:2.0 AS build
WORKDIR /src
COPY Master/Master.csproj Master/
RUN dotnet restore Master/Master.csproj
COPY . .
WORKDIR /src/Master
RUN dotnet build Master.csproj -c Release -o /app

FROM build AS publish
RUN dotnet publish Master.csproj -c Release -o /app -r linux-arm

FROM microsoft/dotnet:2.0-runtime-stretch-arm32v7 AS runtime
ENV ASPNETCORE_URLS http://+:80
WORKDIR /app
COPY --from=publish /app .
ENTRYPOINT ["dotnet", "Master.dll"]